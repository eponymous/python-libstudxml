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

#ifndef PYTHON_STUDXML_H
#define PYTHON_STUDXML_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include <string>
#include <iostream>

#include "libstudxml/parser.hxx"
#include "libstudxml/serializer.hxx"

#include "py_streambuf.h"

#ifndef PyVarObject_HEAD_INIT
#define PyVarObject_HEAD_INIT(type, size) \
        PyObject_HEAD_INIT(type) size,
#endif

#if PY_MAJOR_VERSION >= 3
#if PY_VERSION_HEX >= 0x03050000
typedef PyAsyncMethods* cmpfunc;
#else
typedef void* cmpfunc;
#endif /* PY_VERSION_HEX >= 0x03050000 */
#define PyString_Check(a) PyUnicode_Check(a)
#define PyString_AsString(a) PyUnicode_AsUTF8(a)
#define PyString_FromString(a) PyUnicode_FromString(a)
#endif /* PY_MAJOR_VERSION >= 3 */

#if     __GNUC__ > 2
# define UNUSED(param) param __attribute__((__unused__))
#elif     __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
# define UNUSED(param) __attribute__((__unused__)) param
#else
# define UNUSED(param) param
#endif  /* !__GNUC__ */

namespace xml
{
    class parser;
    class serializer;
    class qname;
}

typedef struct {
    PyObject_HEAD
    xml::parser *obj;
    std::istream *ifs;
    Py_buffer buffer;
} PyXmlParser;

typedef struct {
    PyObject_HEAD
    xml::serializer *obj;
    std::ostream *ofs;
} PyXmlSerializer;

typedef struct {
    PyObject_HEAD
    xml::qname *obj;
} PyXmlQname;

typedef struct {
    PyObject_HEAD
    PyXmlParser *container;
} PyXmlParserIter;

extern PyTypeObject PyXmlParser_Type;
extern PyTypeObject PyXmlParserMeta_Type;
extern PyTypeObject PyXmlSerializer_Type;
extern PyTypeObject PyXmlQname_Type;
extern PyTypeObject PyXmlParserIter_Type;

extern PyTypeObject *PyXmlParsingError_Type;
extern PyTypeObject *PyXmlSerializationError_Type;

#endif /* PYTHON_STUDXML_H */
