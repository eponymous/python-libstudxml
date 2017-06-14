/*
*   Copyright (c) 2006, The Regents of the University of California, 
*   through Lawrence Berkeley National Laboratory (subject to
*   receipt of any required approvals from the U.S. Dept. of Energy).  All
*   rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions are met:
*
*   (1) Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   (2) Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
*   (3) Neither the name of the University of California, Lawrence Berkeley
*   National Laboratory, U.S. Dept. of Energy nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
*   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
*   TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
*   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
*   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*   You are under no obligation whatsoever to provide any bug fixes,
*   patches, or upgrades to the features, functionality or performance of
*   the source code ("Enhancements") to anyone; however, if you choose to
*   make your Enhancements available either publicly, or directly to
*   Lawrence Berkeley National Laboratory, without imposing a separate
*   written license agreement for such Enhancements, then you hereby grant
*   the following license: a non-exclusive, royalty-free perpetual license
*   to install, use, modify, prepare derivative works, incorporate into
*   other computer software, distribute, and sublicense such enhancements or
*   derivative works thereof, in binary and source code form.
*/

#ifndef PYTHON_STREAMBUF_H
#define PYTHON_STREAMBUF_H

#include <Python.h>
#include <streambuf>
#include <iostream>


class py_streambuf : public std::streambuf
{
private:
    typedef std::ios_base ios_base;
    typedef std::streambuf base_t;

public:
    using base_t::char_type;
    using base_t::int_type;
    using base_t::pos_type;
    using base_t::off_type;
    using base_t::traits_type;

    static const std::size_t default_buffer_size = 1024;

    py_streambuf(PyObject* python_file_obj, std::size_t buffer_size_=0) :
        py_object(python_file_obj),
        buffer_size(buffer_size_ != 0 ? buffer_size_ : default_buffer_size)
    {
        setp(0, 0);
        read_buffer = NULL;

        if (PyObject_HasAttrString(py_object, "tell")) {
            PyObject *py_pos = PyObject_CallMethod(py_object, "tell", NULL);

            if (py_pos) {
                end_of_read_buffer = (off_type)PyLong_AsLong(py_pos);
            }
            else {
                end_of_read_buffer = 0;
                PyErr_Clear();
            }

            Py_XDECREF(py_pos);
        }
    }

    virtual ~py_streambuf()
    {
        Py_XDECREF(py_object);
        Py_XDECREF(read_buffer);
    }

    virtual std::streamsize
    showmanyc()
    {
        int_type const failure = traits_type::eof();
        int_type status = underflow();

        if (status == failure) {
            return -1;
        }

        return egptr() - gptr();
    }

    virtual int_type
    underflow()
    {
        int_type const failure = traits_type::eof();

        if (!PyObject_HasAttrString(py_object, "read")) {
            throw std::invalid_argument("That Python file object has no 'read' attribute");
        }

        Py_XDECREF(read_buffer);

        read_buffer = PyObject_CallMethod(py_object, "read", "i", buffer_size);

        char *read_buffer_data;
        Py_ssize_t py_n_read;

        if (PyBytes_AsStringAndSize(read_buffer, &read_buffer_data, &py_n_read) == -1) {
            setg(0, 0, 0);
            Py_XDECREF(read_buffer);
            throw std::invalid_argument("The method 'read' of the Python file object did not return a string.");
        }

        off_type n_read = (off_type)py_n_read;
        end_of_read_buffer += n_read;
        setg(read_buffer_data, read_buffer_data, read_buffer_data + n_read);

        if (n_read == 0) {
            return failure;
        }

        return traits_type::to_int_type(read_buffer_data[0]);
    }

    virtual int_type
    overflow(int_type c=traits_type::eof())
    {
        PyObject *retval;

        if (!PyObject_HasAttrString(py_object, "write")) {
            throw std::invalid_argument("That Python file object has no 'write' attribute");
        }


        if (!traits_type::eq_int_type(c, traits_type::eof())) {
            retval = PyObject_CallMethod(py_object, "write", "C", c);

            if (retval == NULL) {
                throw std::invalid_argument("The method 'write' of the Python file object failed.");
            }

            Py_XDECREF(retval);
        }

        return traits_type::eq_int_type(c, traits_type::eof()) ? traits_type::not_eof(c) : c;
    }

    virtual int
    sync()
    {
        PyObject *retval;
        int result = 0;

        if (gptr() && gptr() < egptr()) {
            if (PyObject_HasAttrString(py_object, "seek")) {
                retval = PyObject_CallMethod(py_object, "seek", "Li", gptr() - egptr(), 1);

                if (retval == NULL) {
                    throw std::invalid_argument("The method 'seek' of the Python file object failed.");
                } else {
                    Py_DECREF(retval);
                }
            }
        }

        return result;
    }

    virtual pos_type
    seekoff(off_type off, ios_base::seekdir way, ios_base::openmode which=ios_base::in|ios_base::out)
    {
        /* In practice, "which" is either std::ios_base::in or out
           since we end up here because either seekp or seekg was called
           on the stream using this buffer. That simplifies the code
           in a few places.
        */
        PyObject *retval;
        off_type result;
        int const failure = off_type(-1);

        if (!PyObject_HasAttrString(py_object, "seek")) {
            throw std::invalid_argument("That Python file object has no 'seek' attribute");
        }

        // we need the read buffer to contain something!
        if (which == ios_base::in && !gptr()) {
            if (traits_type::eq_int_type(underflow(), traits_type::eof())) {
                return failure;
            }
        }

        // compute the whence parameter for Python seek
        int whence;
        switch (way) {
            case ios_base::beg:
                whence = 0;
                break;
            case ios_base::cur:
                whence = 1;
                break;
            case ios_base::end:
                whence = 2;
                break;
            default:
                return failure;
        }

        // we need to call Python
        if (which == ios_base::out) {
            overflow();
        }

        if (way == ios_base::cur) {
            if (which == ios_base::in) {
                off -= egptr() - gptr();
            }
            else if (which == ios_base::out) {
                off += pptr() - pbase();
            }
        }

        retval = PyObject_CallMethod(py_object, "seek", "Li", off, whence);

        if (retval == NULL) {
            throw std::invalid_argument("The method 'seek' of the Python file object failed.");
        } else {
            Py_DECREF(retval);
        }

        retval = PyObject_CallMethod(py_object, "tell", NULL);

        if (retval == NULL) {
            throw std::invalid_argument("The method 'tell' of the Python file object failed.");
        } else {
            result = PyLong_AsLongLong(retval);
            Py_DECREF(retval);
        }

        if (which == ios_base::in) {
            underflow();
        }

        return result;
    }

    virtual pos_type
    seekpos(pos_type sp, ios_base::openmode which=ios_base::in|ios_base::out)
    {
        return py_streambuf::seekoff(sp, ios_base::beg, which);
    }

private:
    PyObject *py_object, *read_buffer;

    std::size_t buffer_size;

    off_type end_of_read_buffer;

public:

    class istream : public std::istream
    {
      public:
        istream(py_streambuf& buf) : std::istream(&buf) {}

        ~istream()
        {
            if (this->good())
                this->sync();
        }
    };

    class ostream : public std::ostream
    {
    public:
        ostream(py_streambuf& buf) : std::ostream(&buf) {}

        ~ostream()
        {
            if (this->good())
                this->flush();
        }
    };
};


struct py_ostream : public py_streambuf::ostream
{
    py_ostream(PyObject *python_file_obj, std::size_t buffer_size=0) :
        py_streambuf::ostream(python_streambuf),
        python_streambuf(python_file_obj, buffer_size)
    {}

    ~py_ostream()
    {
        if (this->good())
            this->flush();
    }

    py_streambuf python_streambuf;
};


struct py_istream : public py_streambuf::istream
{
    py_istream(PyObject *python_file_obj, std::size_t buffer_size=0) :
        py_streambuf::istream(python_streambuf),
        python_streambuf(python_file_obj, buffer_size)
    {}

    ~py_istream()
    {
        if (this->good())
            this->sync();
    }

    py_streambuf python_streambuf;
};

#endif  /* PYTHON_STREAMBUF_H */
