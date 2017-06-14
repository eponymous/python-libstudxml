/*
*   Copyright (c) 2017, Dan Eicher 
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
*/

#include "py_studxml.h"

static PyObject *
PyXmlQname__get_namespace(PyXmlQname *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "s#", (self->obj->namespace_()).c_str(), (self->obj->namespace_()).size());
}

static PyObject *
PyXmlQname__get_name(PyXmlQname *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "s#", (self->obj->name()).c_str(), (self->obj->name()).size());
}

static PyObject *
PyXmlQname__get_prefix(PyXmlQname *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "s#", (self->obj->prefix()).c_str(), (self->obj->prefix()).size());
}

static PyObject *
PyXmlQname__get_empty(PyXmlQname *self, void * UNUSED(closure))
{
    return PyBool_FromLong(self->obj->empty());
}

static PyGetSetDef PyXmlQname__getsets[] = {
    {
        (char*) "namespace", /* attribute name */
        (getter) PyXmlQname__get_namespace, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "name", /* attribute name */
        (getter) PyXmlQname__get_name, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "prefix", /* attribute name */
        (getter) PyXmlQname__get_prefix, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "empty", /* attribute name */
        (getter) PyXmlQname__get_empty, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};

static PyObject *
PyXmlQname__copy__(PyXmlQname *self)
{
    PyXmlQname *py_copy;

    py_copy = PyObject_New(PyXmlQname, &PyXmlQname_Type);
    py_copy->obj = new xml::qname(*self->obj);

    return (PyObject *) py_copy;
}

static PyMethodDef PyXmlQname_methods[] = {
    {(char *) "__copy__", (PyCFunction) PyXmlQname__copy__, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static PyObject *
PyXmlQname__tp_richcompare(PyXmlQname *self, PyObject *other, int opid)
{
    xml::qname right, left = *self->obj;

    if (PyObject_IsInstance(other, (PyObject *) &PyXmlQname_Type)) {
        right = *((PyXmlQname*)other)->obj;
    }
    else if (PyString_Check(other)) {
        right = xml::qname(PyString_AsString(other));
    }
    else if (PyBytes_Check(other)) {
        right = xml::qname(PyBytes_AsString(other));
    }

    if (!right.empty()) {
        switch (opid) {
            case Py_EQ:
                if (left == right) {
                    Py_INCREF(Py_True);
                    return Py_True;
                } else {
                    Py_INCREF(Py_False);
                    return Py_False;
                }
            case Py_NE:
                if (left != right) {
                    Py_INCREF(Py_True);
                    return Py_True;
                } else {
                    Py_INCREF(Py_False);
                    return Py_False;
                }
            default:
                Py_INCREF(Py_NotImplemented);
                return Py_NotImplemented;
        } /* closes switch (opid) */
    }

    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

static int
PyXmlQname__tp_init__0(PyXmlQname *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *keywords[] = {"name", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#", (char **) keywords, &name, &name_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return -1;
    }

    name_std = std::string(name, name_len);

    self->obj = new xml::qname(name_std);

    return 0;
}

static int
PyXmlQname__tp_init__1(PyXmlQname *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *namespace_ = NULL;
    Py_ssize_t namespace_len;
    std::string namespace_std;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *keywords[] = {"namespace", "name", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#", (char **) keywords, &namespace_, &namespace_len, &name, &name_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return -1;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);

    self->obj = new xml::qname(namespace_std, name_std);

    return 0;
}

static int
PyXmlQname__tp_init__2(PyXmlQname *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *namespace_ = NULL;
    Py_ssize_t namespace_len;
    std::string namespace_std;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *prefix = NULL;
    Py_ssize_t prefix_len;
    std::string prefix_std;
    const char *keywords[] = {"namespace", "name", "prefix", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#s#", (char **) keywords,
                                     &namespace_, &namespace_len, &name, &name_len, &prefix, &prefix_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return -1;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);
    prefix_std = std::string(prefix, prefix_len);

    self->obj = new xml::qname(namespace_std, name_std, prefix_std);

    return 0;
}

static int
PyXmlQname__tp_init(PyXmlQname *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[3] = {0,};

    retval = PyXmlQname__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlQname__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlQname__tp_init__2(self, args, kwargs, &exceptions[2]);
    if (!exceptions[2]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        return retval;
    }

    error_list = PyList_New(3);

    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);

    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);

    PyList_SET_ITEM(error_list, 2, PyObject_Str(exceptions[2]));
    Py_DECREF(exceptions[2]);

    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);

    return -1;
}

static void
PyXmlQname__tp_dealloc(PyXmlQname *self)
{
    xml::qname *tmp = self->obj;
    self->obj = NULL;

    delete tmp;

    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
PyXmlQname__tp_str(PyXmlQname *self)
{
    return PyString_FromString(self->obj->string().c_str());
}

PyTypeObject PyXmlQname_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "studxml.Qname",                                      /* tp_name */
    sizeof(PyXmlQname),                                            /* tp_basicsize */
    0,                                                             /* tp_itemsize */
    /* methods */
    (destructor)PyXmlQname__tp_dealloc,                            /* tp_dealloc */
    (printfunc)0,                                                  /* tp_print */
    (getattrfunc)NULL,                                             /* tp_getattr */
    (setattrfunc)NULL,                                             /* tp_setattr */
#if PY_MAJOR_VERSION >= 3
    NULL,
#else
    (cmpfunc)NULL,                                                 /* tp_compare */
#endif
    (reprfunc)NULL,                                                /* tp_repr */
    (PyNumberMethods*)NULL,                                        /* tp_as_number */
    (PySequenceMethods*)NULL,                                      /* tp_as_sequence */
    (PyMappingMethods*)NULL,                                       /* tp_as_mapping */
    (hashfunc)NULL,                                                /* tp_hash */
    (ternaryfunc)NULL,                                             /* tp_call */
    (reprfunc)PyXmlQname__tp_str,                                  /* tp_str */
    (getattrofunc)NULL,                                            /* tp_getattro */
    (setattrofunc)NULL,                                            /* tp_setattro */
    (PyBufferProcs*)NULL,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                                            /* tp_flags */
    "Qname(namespace, name, prefix)\nQname(namespace, name)\nQname(ctor_arg)\nQname(name)", /* Documentation string */
    (traverseproc)NULL,                                            /* tp_traverse */
    (inquiry)NULL,                                                 /* tp_clear */
    (richcmpfunc)PyXmlQname__tp_richcompare,                       /* tp_richcompare */
    0,                                                             /* tp_weaklistoffset */
    (getiterfunc)NULL,                                             /* tp_iter */
    (iternextfunc)NULL,                                            /* tp_iternext */
    (struct PyMethodDef*)PyXmlQname_methods,                       /* tp_methods */
    (struct PyMemberDef*)0,                                        /* tp_members */
    PyXmlQname__getsets,                                           /* tp_getset */
    NULL,                                                          /* tp_base */
    NULL,                                                          /* tp_dict */
    (descrgetfunc)NULL,                                            /* tp_descr_get */
    (descrsetfunc)NULL,                                            /* tp_descr_set */
    0,                                                             /* tp_dictoffset */
    (initproc)PyXmlQname__tp_init,                                 /* tp_init */
    (allocfunc)PyType_GenericAlloc,                                /* tp_alloc */
    (newfunc)PyType_GenericNew,                                    /* tp_new */
    (freefunc)0,                                                   /* tp_free */
    (inquiry)NULL,                                                 /* tp_is_gc */
    NULL,                                                          /* tp_bases */
    NULL,                                                          /* tp_mro */
    NULL,                                                          /* tp_cache */
    NULL,                                                          /* tp_subclasses */
    NULL,                                                          /* tp_weaklist */
    (destructor) NULL                                              /* tp_del */
};

