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
PyXmlSerializer__get_output_name(PyXmlSerializer *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "s#", (self->obj->output_name()).c_str(), (self->obj->output_name()).size());
}

static PyObject *
PyXmlSerializer__get_current_element(PyXmlSerializer *self, void * UNUSED(closure))
{
    PyXmlQname *py_qname;

    try {

        py_qname = PyObject_New(PyXmlQname, &PyXmlQname_Type);
        py_qname->obj = new xml::qname(self->obj->current_element());

        return (PyObject *)py_qname;

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyObject *
PyXmlSerializer__get_current_attribute(PyXmlSerializer *self, void * UNUSED(closure))
{
    PyXmlQname *py_qname;

    try {

        py_qname = PyObject_New(PyXmlQname, &PyXmlQname_Type);
        py_qname->obj = new xml::qname(self->obj->current_attribute());

        return (PyObject *)py_qname;

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyGetSetDef PyXmlSerializer__getsets[] = {
    {
        (char*) "output_name", /* attribute name */
        (getter) PyXmlSerializer__get_output_name, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "current_element", /* attribute name */
        (getter) PyXmlSerializer__get_current_element, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "current_attribute", /* attribute name */
        (getter) PyXmlSerializer__get_current_attribute, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};

static PyObject *
PyXmlSerializer_start_element__0(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyXmlQname *qname;
    const char *keywords[] = {"qname", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyXmlQname_Type, &qname)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {
        self->obj->start_element(*((PyXmlQname *) qname)->obj);



    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_start_element__1(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
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
        return NULL;
    }

    name_std = std::string(name, name_len);

    try {

        self->obj->start_element(name_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_start_element__2(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
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
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);

    try {

        self->obj->start_element(namespace_std, name_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_start_element(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *retval;
    PyObject *error_list;
    PyObject *exceptions[3] = {0,};

    retval = PyXmlSerializer_start_element__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlSerializer_start_element__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlSerializer_start_element__2(self, args, kwargs, &exceptions[2]);
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

    return NULL;
}

static PyObject *
PyXmlSerializer_end_element__0(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {

        self->obj->end_element();

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_end_element__1(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyXmlQname *qname;
    const char *keywords[] = {"qname", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyXmlQname_Type, &qname)) {
        {
            PyObject *exc_type, *traceback;
            PyErr_Fetch(&exc_type, return_exception, &traceback);
            Py_XDECREF(exc_type);
            Py_XDECREF(traceback);
        }
        return NULL;
    }

    try {

        self->obj->end_element(*((PyXmlQname *) qname)->obj);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_end_element__2(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
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
        return NULL;
    }

    name_std = std::string(name, name_len);

    try {

        self->obj->end_element(name_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_end_element__3(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
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
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);

    try {

        self->obj->end_element(namespace_std, name_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_end_element(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    PyObject * retval;
    PyObject *error_list;
    PyObject *exceptions[4] = {0,};

    retval = PyXmlSerializer_end_element__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlSerializer_end_element__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlSerializer_end_element__2(self, args, kwargs, &exceptions[2]);
    if (!exceptions[2]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        return retval;
    }

    retval = PyXmlSerializer_end_element__3(self, args, kwargs, &exceptions[3]);
    if (!exceptions[3]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        return retval;
    }

    error_list = PyList_New(4);

    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);

    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);

    PyList_SET_ITEM(error_list, 2, PyObject_Str(exceptions[2]));
    Py_DECREF(exceptions[2]);

    PyList_SET_ITEM(error_list, 3, PyObject_Str(exceptions[3]));
    Py_DECREF(exceptions[3]);

    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);

    return NULL;
}

static PyObject *
PyXmlSerializer_element__0(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *value = NULL;
    Py_ssize_t value_len;
    std::string value_std;
    const char *keywords[] = {"value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#", (char **) keywords, &value, &value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    value_std = std::string(value, value_len);

    try {

        self->obj->element(value_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_element__1(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *value = NULL;
    Py_ssize_t value_len;
    std::string value_std;
    const char *keywords[] = {"name", "value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#", (char **) keywords, &name, &name_len, &value, &value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    name_std = std::string(name, name_len);
    value_std = std::string(value, value_len);

    try {

        self->obj->element(name_std, value_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_element__2(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyXmlQname *qname;
    const char *value = NULL;
    Py_ssize_t value_len;
    std::string value_std;
    const char *keywords[] = {"qname", "value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!s#", (char **) keywords, &PyXmlQname_Type, &qname, &value, &value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    value_std = std::string(value, value_len);

    try {

        self->obj->element(*((PyXmlQname *) qname)->obj, value_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_element__3(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *namespace_ = NULL;
    Py_ssize_t namespace_len;
    std::string namespace_std;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *value = NULL;
    Py_ssize_t value_len;
    std::string value_std;
    const char *keywords[] = {"namespace", "name", "value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#s#", (char **) keywords,
                                     &namespace_, &namespace_len, &name, &name_len, &value, &value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);
    value_std = std::string(value, value_len);

    try {

        self->obj->element(namespace_std, name_std, value_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_element(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *retval;
    PyObject *error_list;
    PyObject *exceptions[4] = {0,};

    retval = PyXmlSerializer_element__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlSerializer_element__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlSerializer_element__2(self, args, kwargs, &exceptions[2]);
    if (!exceptions[2]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        return retval;
    }

    retval = PyXmlSerializer_element__3(self, args, kwargs, &exceptions[3]);
    if (!exceptions[3]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        return retval;
    }

    error_list = PyList_New(4);

    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);

    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);

    PyList_SET_ITEM(error_list, 2, PyObject_Str(exceptions[2]));
    Py_DECREF(exceptions[2]);

    PyList_SET_ITEM(error_list, 3, PyObject_Str(exceptions[3]));
    Py_DECREF(exceptions[3]);

    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);

    return NULL;
}

static PyObject *
PyXmlSerializer_start_attribute__0(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyXmlQname *qname;
    const char *keywords[] = {"qname", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyXmlQname_Type, &qname)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {

        self->obj->start_attribute(*((PyXmlQname *) qname)->obj);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_start_attribute__1(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
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
        return NULL;
    }

    name_std = std::string(name, name_len);

    try {

        self->obj->start_attribute(name_std);


    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_start_attribute__2(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
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
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);

    try {

        self->obj->start_attribute(namespace_std, name_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_start_attribute(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    PyObject * retval;
    PyObject *error_list;
    PyObject *exceptions[3] = {0,};

    retval = PyXmlSerializer_start_attribute__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlSerializer_start_attribute__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlSerializer_start_attribute__2(self, args, kwargs, &exceptions[2]);
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

    return NULL;
}

static PyObject *
PyXmlSerializer_end_attribute__0(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *keywords[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {

        self->obj->end_attribute();

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_end_attribute__1(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyXmlQname *qname;
    const char *keywords[] = {"qname", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyXmlQname_Type, &qname)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {

        self->obj->end_attribute(*((PyXmlQname *) qname)->obj);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_end_attribute__2(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
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
        return NULL;
    }

    name_std = std::string(name, name_len);

    try {

        self->obj->end_attribute(name_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_end_attribute__3(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
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
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);

    try {

        self->obj->end_attribute(namespace_std, name_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_end_attribute(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *retval;
    PyObject *error_list;
    PyObject *exceptions[4] = {0,};

    retval = PyXmlSerializer_end_attribute__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlSerializer_end_attribute__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlSerializer_end_attribute__2(self, args, kwargs, &exceptions[2]);
    if (!exceptions[2]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        return retval;
    }

    retval = PyXmlSerializer_end_attribute__3(self, args, kwargs, &exceptions[3]);
    if (!exceptions[3]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        return retval;
    }

    error_list = PyList_New(4);

    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);

    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);

    PyList_SET_ITEM(error_list, 2, PyObject_Str(exceptions[2]));
    Py_DECREF(exceptions[2]);

    PyList_SET_ITEM(error_list, 3, PyObject_Str(exceptions[3]));
    Py_DECREF(exceptions[3]);

    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);

    return NULL;
}

static PyObject *
PyXmlSerializer_attribute__0(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *value = NULL;
    Py_ssize_t value_len;
    std::string value_std;
    const char *keywords[] = {"name", "value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#", (char **) keywords, &name, &name_len, &value, &value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    name_std = std::string(name, name_len);
    value_std = std::string(value, value_len);

    try {

        self->obj->attribute(name_std, value_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_attribute__1(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    PyXmlQname *qname;
    const char *value = NULL;
    Py_ssize_t value_len;
    std::string value_std;
    const char *keywords[] = {"qname", "value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!s#", (char **) keywords, &PyXmlQname_Type, &qname, &value, &value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    value_std = std::string(value, value_len);

    try {

        self->obj->attribute(*((PyXmlQname *) qname)->obj, value_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_attribute__2(PyXmlSerializer *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    const char *namespace_ = NULL;
    Py_ssize_t namespace_len;
    std::string namespace_std;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *value = NULL;
    Py_ssize_t value_len;
    std::string value_std;
    const char *keywords[] = {"namespace", "name", "value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#s#", (char **) keywords,
                                     &namespace_, &namespace_len, &name, &name_len, &value, &value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);
    value_std = std::string(value, value_len);

    try {

        self->obj->attribute(namespace_std, name_std, value_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_attribute(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *retval;
    PyObject *error_list;
    PyObject *exceptions[3] = {0,};

    retval = PyXmlSerializer_attribute__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlSerializer_attribute__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlSerializer_attribute__2(self, args, kwargs, &exceptions[2]);
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

    return NULL;
}

static PyObject *
PyXmlSerializer_characters(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    const char *value = NULL;
    Py_ssize_t value_len;
    std::string value_std;
    const char *keywords[] = {"value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#", (char **) keywords, &value, &value_len)) {
        return NULL;
    }

    value_std = std::string(value, value_len);

    try {

        self->obj->characters(value_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_namespace_decl(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    const char *namespace_ = NULL;
    Py_ssize_t namespace_len;
    std::string namespace_std;
    const char *prefix = NULL;
    Py_ssize_t prefix_len;
    std::string prefix_std;
    const char *keywords[] = {"namespace", "prefix", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#", (char **) keywords, &namespace_, &namespace_len, &prefix, &prefix_len)) {
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    prefix_std = std::string(prefix, prefix_len);

    try {

        self->obj->namespace_decl(namespace_std, prefix_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_xml_decl(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    const char *version = NULL;
    Py_ssize_t version_len;
    std::string version_std;
    const char *encoding = NULL;
    Py_ssize_t encoding_len;
    std::string encoding_std;
    const char *standalone = NULL;
    Py_ssize_t standalone_len;
    std::string standalone_std;
    const char *keywords[] = {"version", "encoding", "standalone", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "|s#s#s#", (char **) keywords,
                                     &version, &version_len, &encoding, &encoding_len, &standalone, &standalone_len)) {
        return NULL;
    }

    if (version)
        version_std = std::string(version, version_len);
    else
        version_std = "1.0";

    if (encoding)
        encoding_std = std::string(encoding, encoding_len);
    else
        encoding_std = "UTF-8";

    if (standalone)
        standalone_std = std::string(standalone, standalone_len);
    else
        standalone_std = "";

    try {

        self->obj->xml_decl(version_std, encoding_std, standalone_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_doctype_decl(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    const char *root_element = NULL;
    Py_ssize_t root_element_len;
    std::string root_element_std;
    const char *public_id = NULL;
    Py_ssize_t public_id_len;
    std::string public_id_std;
    const char *system_id = NULL;
    Py_ssize_t system_id_len;
    std::string system_id_std;
    const char *internal_subset = NULL;
    Py_ssize_t internal_subset_len;
    std::string internal_subset_std;
    const char *keywords[] = {"root_element", "public_id", "system_id", "internal_subset", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#|s#s#s#", (char **) keywords, &root_element, &root_element_len, &public_id, &public_id_len, &system_id, &system_id_len, &internal_subset, &internal_subset_len)) {
        return NULL;
    }

    root_element_std = std::string(root_element, root_element_len);

    if (public_id)
        public_id_std = std::string(public_id, public_id_len);
    else
        public_id_std = "";

    if (system_id)
        system_id_std = std::string(system_id, system_id_len);
    else
        system_id_std = "";

    if (internal_subset)
        internal_subset_std = std::string(internal_subset, internal_subset_len);
    else
        internal_subset_std = "";

    try {

        self->obj->doctype_decl(root_element_std, public_id_std, system_id_std, internal_subset_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlSerializer_lookup_namespace_prefix(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    bool retval;
    const char *namespace_ = NULL;
    Py_ssize_t namespace_len;
    std::string namespace_std;
    const char *prefix = NULL;
    Py_ssize_t prefix_len;
    std::string prefix_std;
    const char *keywords[] = {"namespace", "prefix", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#", (char **) keywords,
                                     &namespace_, &namespace_len, &prefix, &prefix_len)) {
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    prefix_std = std::string(prefix, prefix_len);

    try {

        retval = self->obj->lookup_namespace_prefix(namespace_std, prefix_std);

    } catch (xml::serialization const &exc) {

        PyErr_SetString((PyObject *) PyXmlSerializationError_Type, exc.what());

        return NULL;
    }

    return PyBool_FromLong(retval);
}

static PyObject *
PyXmlSerializer_suspend_indentation(PyXmlSerializer *self)
{
    self->obj->suspend_indentation();

    Py_RETURN_NONE;
}


static PyObject *
PyXmlSerializer_resume_indentation(PyXmlSerializer *self)
{
    self->obj->resume_indentation();

    Py_RETURN_NONE;
}


PyObject *
PyXmlSerializer_indentation_suspended(PyXmlSerializer *self)
{
    return Py_BuildValue((char *) "K", ((unsigned PY_LONG_LONG) self->obj->indentation_suspended()));
}

static PyMethodDef PyXmlSerializer_methods[] = {
    {
        (char *) "start_element",
        (PyCFunction) PyXmlSerializer_start_element,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "end_element",
        (PyCFunction) PyXmlSerializer_end_element,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "element",
        (PyCFunction) PyXmlSerializer_element,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "start_attribute",
        (PyCFunction) PyXmlSerializer_start_attribute,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "end_attribute",
        (PyCFunction) PyXmlSerializer_end_attribute,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "attribute",
        (PyCFunction) PyXmlSerializer_attribute,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "characters",
        (PyCFunction) PyXmlSerializer_characters,
        METH_KEYWORDS|METH_VARARGS,
        "characters(value)\n\ntype: value: std::string const &"
    },
    {
        (char *) "namespace_decl",
        (PyCFunction) PyXmlSerializer_namespace_decl,
        METH_KEYWORDS|METH_VARARGS,
        "namespace_decl(namespace, prefix)\n\ntype: namespace: std::string const &\ntype: prefix: std::string const &"
    },
    {
        (char *) "xml_decl",
        (PyCFunction) PyXmlSerializer_xml_decl,
        METH_KEYWORDS|METH_VARARGS,
        "xml_decl(version, encoding, standalone)\n\ntype: version: std::string const &\ntype: encoding: std::string const &\ntype: standalone: std::string const &"
    },
    {
        (char *) "doctype_decl",
        (PyCFunction) PyXmlSerializer_doctype_decl,
        METH_KEYWORDS|METH_VARARGS,
        "doctype_decl(root_element, public_id, system_id, internal_subset)\n\ntype: root_element: std::string const &\ntype: public_id: std::string const &\ntype: system_id: std::string const &\ntype: internal_subset: std::string const &"
    },
    {
        (char *) "lookup_namespace_prefix",
        (PyCFunction) PyXmlSerializer_lookup_namespace_prefix,
        METH_KEYWORDS|METH_VARARGS,
        "lookup_namespace_prefix(namespace, prefix)\n\ntype: namespace: std::string const &\ntype: prefix: std::string const &"
    },
    {
        (char *) "suspend_indentation",
        (PyCFunction) PyXmlSerializer_suspend_indentation,
        METH_NOARGS,
        "suspend_indentation()\n\n"
    },
    {
        (char *) "resume_indentation",
        (PyCFunction) PyXmlSerializer_resume_indentation,
        METH_NOARGS,
        "resume_indentation()\n\n"
    },
    {
        (char *) "indentation_suspended",
        (PyCFunction) PyXmlSerializer_indentation_suspended,
        METH_NOARGS,
        "indentation_suspended()\n\n"
    },
    {NULL, NULL, 0, NULL}
};

extern PyTypeObject PyIOBase_Type;

static int
PyXmlSerializer__tp_init(PyXmlSerializer *self, PyObject *args, PyObject *kwargs)
{
    PyObject *in;
    std::string out_std;
    const char *output_name = NULL;
    Py_ssize_t output_name_len;
    std::string output_name_std;
    int indentation = 2;
    const char *keywords[] = {"in", "output_name", "indentation", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!|s#i", (char **) keywords,
                                     &PyIOBase_Type, &in, &output_name, &output_name_len, &indentation)) {
        return -1;
    }

    if (indentation > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");
        return -1;
    }

    if (output_name)
        output_name_std = std::string(output_name, output_name_len);
    else
        output_name_std = "";

    Py_INCREF(in);

    self->ofs = new py_ostream(in);
    self->obj = new xml::serializer(*self->ofs, output_name_std, indentation);

    return 0;
}

static void
PyXmlSerializer__tp_dealloc(PyXmlSerializer *self)
{
    xml::serializer *tmp = self->obj;
    std::ostream *ofs = self->ofs;

    self->obj = NULL;

    delete tmp;
    delete ofs;

    Py_TYPE(self)->tp_free((PyObject *)self);
}

PyTypeObject PyXmlSerializer_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "studxml.Serializer",                                 /* tp_name */
    sizeof(PyXmlSerializer),                                       /* tp_basicsize */
    0,                                                             /* tp_itemsize */
    /* methods */
    (destructor)PyXmlSerializer__tp_dealloc,                       /* tp_dealloc */
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
    (reprfunc)NULL,                                                /* tp_str */
    (getattrofunc)NULL,                                            /* tp_getattro */
    (setattrofunc)NULL,                                            /* tp_setattro */
    (PyBufferProcs*)NULL,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                                            /* tp_flags */
    "Serializer(out, output_name, indentation)",                   /* Documentation string */
    (traverseproc)NULL,                                            /* tp_traverse */
    (inquiry)NULL,                                                 /* tp_clear */
    (richcmpfunc)NULL,                                             /* tp_richcompare */
    0,                                                             /* tp_weaklistoffset */
    (getiterfunc)NULL,                                             /* tp_iter */
    (iternextfunc)NULL,                                            /* tp_iternext */
    (struct PyMethodDef*)PyXmlSerializer_methods,                  /* tp_methods */
    (struct PyMemberDef*)0,                                        /* tp_members */
    PyXmlSerializer__getsets,                                      /* tp_getset */
    NULL,                                                          /* tp_base */
    NULL,                                                          /* tp_dict */
    (descrgetfunc)NULL,                                            /* tp_descr_get */
    (descrsetfunc)NULL,                                            /* tp_descr_set */
    0,                                                             /* tp_dictoffset */
    (initproc)PyXmlSerializer__tp_init,                            /* tp_init */
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

