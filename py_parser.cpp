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
PyXmlParser__get_qname(PyXmlParser *self, void * UNUSED(closure))
{
    PyXmlQname *py_qname;

    py_qname = PyObject_New(PyXmlQname, &PyXmlQname_Type);
    py_qname->obj = new xml::qname(self->obj->qname());

    return (PyObject *)py_qname;
}

static PyObject *
PyXmlParser__get_namespace(PyXmlParser *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "s#", (self->obj->namespace_()).c_str(), (self->obj->namespace_()).size());
}

static PyObject *
PyXmlParser__get_name(PyXmlParser *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "s#", (self->obj->name()).c_str(), (self->obj->name()).size());
}

static PyObject *
PyXmlParser__get_prefix(PyXmlParser *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "s#", (self->obj->prefix()).c_str(), (self->obj->prefix()).size());
}

static PyObject *
PyXmlParser__get_value(PyXmlParser *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "s#", (self->obj->value()).c_str(), (self->obj->value()).size());
}

static PyObject *
PyXmlParser__get_line(PyXmlParser *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "K", self->obj->line());
}

static PyObject *
PyXmlParser__get_column(PyXmlParser *self, void * UNUSED(closure))
{
    return Py_BuildValue((char *) "K", self->obj->column());
}

static PyObject *
PyXmlParser__get_content(PyXmlParser *self, void * UNUSED(closure))
{
    return PyLong_FromLong(self->obj->content());
}

static int
PyXmlParser__set_content(PyXmlParser *self, PyObject *value, void * UNUSED(closure))
{
    self->obj->content((xml::content::value)PyLong_AsLong(value));
    return 0;
}

static PyGetSetDef PyXmlParser__getsets[] = {
    {
        (char*) "qname", /* attribute name */
        (getter) PyXmlParser__get_qname, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "namespace", /* attribute name */
        (getter) PyXmlParser__get_namespace, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "name", /* attribute name */
        (getter) PyXmlParser__get_name, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "prefix", /* attribute name */
        (getter) PyXmlParser__get_prefix, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "value", /* attribute name */
        (getter) PyXmlParser__get_value, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "line", /* attribute name */
        (getter) PyXmlParser__get_line, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "column", /* attribute name */
        (getter) PyXmlParser__get_column, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "content", /* attribute name */
        (getter) PyXmlParser__get_content, /* C function to get the attribute */
        (setter) PyXmlParser__set_content, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};

static PyObject *
PyXmlParser_next(PyXmlParser *self)
{
    try {

        return Py_BuildValue((char *) "i", self->obj->next());

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyObject *
PyXmlParser_next_expect__0(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    xml::parser::event_type event_type;
    const char *keywords[] = {"event_type", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "i", (char **) keywords, &event_type)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {

        self->obj->next_expect(event_type);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlParser_next_expect__1(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    xml::parser::event_type event_type;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *keywords[] = {"event_type", "name", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "is#", (char **) keywords, &event_type, &name, &name_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    name_std = std::string(name, name_len);

    try {

        self->obj->next_expect(event_type, name_std);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlParser_next_expect__2(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    xml::parser::event_type event_type;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    xml::content::value content;
    const char *keywords[] = {"event_type", "name", "content", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "is#i", (char **) keywords,
                                     &event_type, &name, &name_len, &content)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    name_std = std::string(name, name_len);

    try {

        self->obj->next_expect(event_type, name_std, content);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlParser_next_expect__3(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    xml::parser::event_type event_type;
    PyXmlQname *qname;
    const char *keywords[] = {"event_type", "qname", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iO!", (char **) keywords, &event_type, &PyXmlQname_Type, &qname)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {

        self->obj->next_expect(event_type, *((PyXmlQname *) qname)->obj);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlParser_next_expect__4(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    xml::parser::event_type event_type;
    PyXmlQname *qname;
    xml::content::value content;
    const char *keywords[] = {"event_type", "qname", "content", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iO!i", (char **) keywords,
                                     &event_type, &PyXmlQname_Type, &qname, &content)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {

        self->obj->next_expect(event_type, *((PyXmlQname *) qname)->obj, content);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlParser_next_expect__5(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    xml::parser::event_type event_type;
    const char *namespace_ = NULL;
    Py_ssize_t namespace_len;
    std::string namespace_std;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *keywords[] = {"event_type", "namespace", "name", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "is#s#", (char **) keywords,
                                     &event_type, &namespace_, &namespace_len, &name, &name_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);

    try {

        self->obj->next_expect(event_type, namespace_std, name_std);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlParser_next_expect__6(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    xml::parser::event_type event_type;
    const char *namespace_ = NULL;
    Py_ssize_t namespace_len;
    std::string namespace_std;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    xml::content::value content;
    const char *keywords[] = {"event_type", "namespace", "name", "content", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "is#s#i", (char **) keywords,
                                     &event_type, &namespace_, &namespace_len, &name, &name_len, &content)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    namespace_std = std::string(namespace_, namespace_len);
    name_std = std::string(name, name_len);

    try {

        self->obj->next_expect(event_type, namespace_std, name_std, content);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
PyXmlParser_next_expect(PyXmlParser *self, PyObject *args, PyObject *kwargs)
{
    PyObject *retval;
    PyObject *error_list;
    PyObject *exceptions[7] = {0,};

    retval = PyXmlParser_next_expect__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlParser_next_expect__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlParser_next_expect__2(self, args, kwargs, &exceptions[2]);
    if (!exceptions[2]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        return retval;
    }

    retval = PyXmlParser_next_expect__3(self, args, kwargs, &exceptions[3]);
    if (!exceptions[3]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        return retval;
    }

    retval = PyXmlParser_next_expect__4(self, args, kwargs, &exceptions[4]);
    if (!exceptions[4]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        Py_DECREF(exceptions[3]);
        return retval;
    }

    retval = PyXmlParser_next_expect__5(self, args, kwargs, &exceptions[5]);
    if (!exceptions[5]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        Py_DECREF(exceptions[3]);
        Py_DECREF(exceptions[4]);
        return retval;
    }

    retval = PyXmlParser_next_expect__6(self, args, kwargs, &exceptions[6]);
    if (!exceptions[6]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        Py_DECREF(exceptions[3]);
        Py_DECREF(exceptions[4]);
        Py_DECREF(exceptions[5]);
        return retval;
    }

    error_list = PyList_New(7);

    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);

    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);

    PyList_SET_ITEM(error_list, 2, PyObject_Str(exceptions[2]));
    Py_DECREF(exceptions[2]);

    PyList_SET_ITEM(error_list, 3, PyObject_Str(exceptions[3]));
    Py_DECREF(exceptions[3]);

    PyList_SET_ITEM(error_list, 4, PyObject_Str(exceptions[4]));
    Py_DECREF(exceptions[4]);

    PyList_SET_ITEM(error_list, 5, PyObject_Str(exceptions[5]));
    Py_DECREF(exceptions[5]);

    PyList_SET_ITEM(error_list, 6, PyObject_Str(exceptions[6]));
    Py_DECREF(exceptions[6]);

    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);

    return NULL;
}

static PyObject *
PyXmlParser_peek(PyXmlParser *self)
{
    return Py_BuildValue((char *) "i", self->obj->peek());
}

static PyObject *
PyXmlParser_event(PyXmlParser *self)
{
    return Py_BuildValue((char *) "i", self->obj->event());
}

static PyObject *
PyXmlParser_attribute__0(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *default_value = NULL;
    Py_ssize_t default_value_len;
    std::string default_value_std;
    const char *keywords[] = {"name", "default_value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#", (char **) keywords, &name, &name_len, &default_value, &default_value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    name_std = std::string(name, name_len);


    try {

        default_value_std = std::string(default_value, default_value_len);

        retval = self->obj->attribute(name_std, default_value_std);

        return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyObject *
PyXmlParser_attribute__1(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
    PyXmlQname *qname;
    const char *default_value = NULL;
    Py_ssize_t default_value_len;
    std::string default_value_std;
    const char *keywords[] = {"qname", "default_value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!s#", (char **) keywords,
                                     &PyXmlQname_Type, &qname, &default_value, &default_value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    default_value_std = std::string(default_value, default_value_len);

    try {
        retval = self->obj->attribute(*((PyXmlQname *) qname)->obj, default_value_std);

        return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyObject *
PyXmlParser_attribute__2(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
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

        retval = self->obj->attribute(name_std);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());
}

static PyObject *
PyXmlParser_attribute__3(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
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

        retval = self->obj->attribute(*((PyXmlQname *) qname)->obj);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());
}

static PyObject *
PyXmlParser_attribute(PyXmlParser *self, PyObject *args, PyObject *kwargs)
{
    PyObject *retval;
    PyObject *error_list;
    PyObject *exceptions[4] = {0,};

    retval = PyXmlParser_attribute__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlParser_attribute__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlParser_attribute__2(self, args, kwargs, &exceptions[2]);
    if (!exceptions[2]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        return retval;
    }

    retval = PyXmlParser_attribute__3(self, args, kwargs, &exceptions[3]);
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
PyXmlParser_attribute_present__0(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    bool retval;
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

        retval = self->obj->attribute_present(name_std);

        return PyBool_FromLong(retval);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyObject *
PyXmlParser_attribute_present__1(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    bool retval;
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
        retval = self->obj->attribute_present(*((PyXmlQname *) qname)->obj);

        return PyBool_FromLong(retval);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyObject *
PyXmlParser_attribute_present(PyXmlParser *self, PyObject *args, PyObject *kwargs)
{
    PyObject *retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};

    retval = PyXmlParser_attribute_present__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlParser_attribute_present__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    error_list = PyList_New(2);

    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);

    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);

    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);

    return NULL;
}

static PyObject *
PyXmlParser_element__0(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
    const char *keywords[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    try {

        retval = self->obj->element();

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());
}

static PyObject *
PyXmlParser_element__1(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
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

        retval = self->obj->element(name_std);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());
}

static PyObject *
PyXmlParser_element__2(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
    const char *name = NULL;
    Py_ssize_t name_len;
    std::string name_std;
    const char *default_value = NULL;
    Py_ssize_t default_value_len;
    std::string default_value_std;
    const char *keywords[] = {"name", "default_value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s#s#", (char **) keywords, &name, &name_len, &default_value, &default_value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    name_std = std::string(name, name_len);
    default_value_std = std::string(default_value, default_value_len);

    try {

        retval = self->obj->element(name_std, default_value_std);

        return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyObject *
PyXmlParser_element__3(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
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

        retval = self->obj->element(*((PyXmlQname *) qname)->obj);

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());
}

static PyObject *
PyXmlParser_element__4(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    std::string retval;
    PyXmlQname *qname;
    const char *default_value = NULL;
    Py_ssize_t default_value_len;
    std::string default_value_std;
    const char *keywords[] = {"qname", "default_value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!s#", (char **) keywords,
                                     &PyXmlQname_Type, &qname, &default_value, &default_value_len)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);
        return NULL;
    }

    default_value_std = std::string(default_value, default_value_len);

    try {
        retval = self->obj->element(*((PyXmlQname *) qname)->obj, default_value_std);

        return Py_BuildValue((char *) "s#", (retval).c_str(), (retval).size());

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }
}

static PyObject *
PyXmlParser_element(PyXmlParser *self, PyObject *args, PyObject *kwargs)
{
    PyObject * retval;
    PyObject *error_list;
    PyObject *exceptions[5] = {0,};

    retval = PyXmlParser_element__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlParser_element__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    retval = PyXmlParser_element__2(self, args, kwargs, &exceptions[2]);
    if (!exceptions[2]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        return retval;
    }

    retval = PyXmlParser_element__3(self, args, kwargs, &exceptions[3]);
    if (!exceptions[3]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        return retval;
    }

    retval = PyXmlParser_element__4(self, args, kwargs, &exceptions[4]);
    if (!exceptions[4]) {
        Py_DECREF(exceptions[0]);
        Py_DECREF(exceptions[1]);
        Py_DECREF(exceptions[2]);
        Py_DECREF(exceptions[3]);
        return retval;
    }

    error_list = PyList_New(5);

    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);

    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);

    PyList_SET_ITEM(error_list, 2, PyObject_Str(exceptions[2]));
    Py_DECREF(exceptions[2]);

    PyList_SET_ITEM(error_list, 3, PyObject_Str(exceptions[3]));
    Py_DECREF(exceptions[3]);

    PyList_SET_ITEM(error_list, 4, PyObject_Str(exceptions[4]));
    Py_DECREF(exceptions[4]);

    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);

    return NULL;
}

static PyMethodDef PyXmlParser_methods[] = {
    {
        (char *) "next",
        (PyCFunction) PyXmlParser_next,
        METH_NOARGS,
        "next()\n\n"
    },
    {
        (char *) "next_expect",
        (PyCFunction) PyXmlParser_next_expect,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "peek",
        (PyCFunction) PyXmlParser_peek,
        METH_NOARGS,
        "peek()\n\n" },
    {
        (char *) "event",
        (PyCFunction) PyXmlParser_event,
        METH_NOARGS,
        "event()\n\n"
    },
    {
        (char *) "attribute",
        (PyCFunction) PyXmlParser_attribute,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "attribute_present",
        (PyCFunction) PyXmlParser_attribute_present,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {
        (char *) "element",
        (PyCFunction) PyXmlParser_element,
        METH_KEYWORDS|METH_VARARGS,
        NULL
    },
    {NULL, NULL, 0, NULL}
};

static PyObject *
PyXmlParser__tp_iter(PyXmlParser *self)
{
    PyXmlParserIter *iter = PyObject_GC_New(PyXmlParserIter, &PyXmlParserIter_Type);
    Py_INCREF(self);
    iter->container = self;
    return (PyObject *) iter;
}

extern PyTypeObject PyIOBase_Type;

static int
PyXmlParser__tp_init__0(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    Py_buffer buffer = {NULL, NULL};
    PyObject *in;
    const char *input_name = NULL;
    Py_ssize_t input_name_len;
    std::string input_name_std;
    int feature = xml::parser::receive_default;
    const char *keywords[] = {"in", "input_name", "feature", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!|s#i", (char **) keywords,
                                     &PyIOBase_Type, &in, &input_name, &input_name_len, &feature)) {
        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);

        return -1;
    }

    if (feature > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");

        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);

        return -1;
    }

    if (input_name)
        input_name_std = std::string(input_name, input_name_len);
    else
        input_name_std = "";

    Py_INCREF((PyObject*) in);

    self->ifs = new py_istream(in);
    self->obj = new xml::parser(*self->ifs, input_name_std, feature);
    self->buffer = buffer;

    return 0;
}

static int
PyXmlParser__tp_init__1(PyXmlParser *self, PyObject *args, PyObject *kwargs, PyObject **return_exception)
{
    Py_buffer buffer = {NULL, NULL};
    const char *input_name = NULL;
    Py_ssize_t input_name_len;
    std::string input_name_std;
    int feature = xml::parser::receive_default;
    const char *keywords[] = {"data", "input_name", "feature", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "s*|s#i", (char **) keywords,
                                     &buffer, &input_name, &input_name_len, &feature)) {
        if (buffer.obj)
            PyBuffer_Release(&buffer);

        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);

        return -1;
    }

    if (input_name)
        input_name_std = std::string(input_name, input_name_len);
    else
        input_name_std = "";

    if (feature > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Out of range");

        PyBuffer_Release(&buffer);

        PyObject *exc_type, *traceback;
        PyErr_Fetch(&exc_type, return_exception, &traceback);
        Py_XDECREF(exc_type);
        Py_XDECREF(traceback);

        return -1;
    }

    self->obj = new xml::parser(buffer.buf, buffer.len, input_name_std, feature);
    self->buffer = buffer;
    self->ifs = NULL;

    return 0;
}

static int
PyXmlParser__tp_init(PyXmlParser *self, PyObject *args, PyObject *kwargs)
{
    int retval;
    PyObject *error_list;
    PyObject *exceptions[2] = {0,};

    retval = PyXmlParser__tp_init__0(self, args, kwargs, &exceptions[0]);
    if (!exceptions[0]) {
        return retval;
    }

    retval = PyXmlParser__tp_init__1(self, args, kwargs, &exceptions[1]);
    if (!exceptions[1]) {
        Py_DECREF(exceptions[0]);
        return retval;
    }

    error_list = PyList_New(2);

    PyList_SET_ITEM(error_list, 0, PyObject_Str(exceptions[0]));
    Py_DECREF(exceptions[0]);

    PyList_SET_ITEM(error_list, 1, PyObject_Str(exceptions[1]));
    Py_DECREF(exceptions[1]);

    PyErr_SetObject(PyExc_TypeError, error_list);
    Py_DECREF(error_list);

    return -1;
}

static void
PyXmlParser__tp_dealloc(PyXmlParser *self)
{
    xml::parser *tmp = self->obj;
    std::istream *ifs = self->ifs;
    self->obj = NULL;

    delete tmp;

    if (ifs) {
        delete ifs;
    }

    if (self->buffer.obj) {
        PyBuffer_Release(&self->buffer);
    }

    Py_TYPE(self)->tp_free((PyObject *)self);
}

PyTypeObject PyXmlParser_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "studxml.Parser",                                     /* tp_name */
    sizeof(PyXmlParser),                                           /* tp_basicsize */
    0,                                                             /* tp_itemsize */
    /* methods */
    (destructor)PyXmlParser__tp_dealloc,                           /* tp_dealloc */
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
    "Parser(in, input_name, feature)",                             /* Documentation string */
    (traverseproc)NULL,                                            /* tp_traverse */
    (inquiry)NULL,                                                 /* tp_clear */
    (richcmpfunc)NULL,                                             /* tp_richcompare */
    0,                                                             /* tp_weaklistoffset */
    (getiterfunc)PyXmlParser__tp_iter,                             /* tp_iter */
    (iternextfunc)NULL,                                            /* tp_iternext */
    (struct PyMethodDef*)PyXmlParser_methods,                      /* tp_methods */
    (struct PyMemberDef*)0,                                        /* tp_members */
    PyXmlParser__getsets,                                          /* tp_getset */
    NULL,                                                          /* tp_base */
    NULL,                                                          /* tp_dict */
    (descrgetfunc)NULL,                                            /* tp_descr_get */
    (descrsetfunc)NULL,                                            /* tp_descr_set */
    0,                                                             /* tp_dictoffset */
    (initproc)PyXmlParser__tp_init,                                /* tp_init */
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

static PyObject *
PyXmlParser__get_receive_elements(PyObject * UNUSED(obj), void * UNUSED(closure))
{
    return Py_BuildValue((char *) "i", xml::parser::receive_elements);
}

static PyObject *
PyXmlParser__get_receive_characters(PyObject * UNUSED(obj), void * UNUSED(closure))
{
    return Py_BuildValue((char *) "i", xml::parser::receive_characters);
}

static PyObject *
PyXmlParser__get_receive_attributes_map(PyObject * UNUSED(obj), void * UNUSED(closure))
{
    return Py_BuildValue((char *) "i", xml::parser::receive_attributes_map);
}

static PyObject *
PyXmlParser__get_receive_attributes_event(PyObject * UNUSED(obj), void * UNUSED(closure))
{
    return Py_BuildValue((char *) "i", xml::parser::receive_attributes_event);
}

static PyObject *
PyXmlParser__get_receive_namespace_decls(PyObject * UNUSED(obj), void * UNUSED(closure))
{
    return Py_BuildValue((char *) "i", xml::parser::receive_namespace_decls);
}

static PyObject *
PyXmlParser__get_receive_default(PyObject * UNUSED(obj), void * UNUSED(closure))
{
    return Py_BuildValue((char *) "i", xml::parser::receive_default);
}

static PyGetSetDef XmlParserMeta__getsets[] = {
    {
        (char*) "receive_elements", /* attribute name */
        (getter) PyXmlParser__get_receive_elements, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "receive_characters", /* attribute name */
        (getter) PyXmlParser__get_receive_characters, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "receive_attributes_map", /* attribute name */
        (getter) PyXmlParser__get_receive_attributes_map, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "receive_attributes_event", /* attribute name */
        (getter) PyXmlParser__get_receive_attributes_event, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "receive_namespace_decls", /* attribute name */
        (getter) PyXmlParser__get_receive_namespace_decls, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "receive_default", /* attribute name */
        (getter) PyXmlParser__get_receive_default, /* C function to get the attribute */
        (setter) NULL, /* C function to set the attribute */
        NULL, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject PyXmlParserMeta_Type = {
        PyVarObject_HEAD_INIT(NULL, 0)
	(char *) "XmlParserMeta",		                   /* tp_name */
	0,					                   /* tp_basicsize */
	0,					                   /* tp_itemsize */
	0,	 				                   /* tp_dealloc */
	0,					                   /* tp_print */
	0,					                   /* tp_getattr */
	0,					                   /* tp_setattr */
	0,					                   /* tp_compare */
	0,					                   /* tp_repr */
	0,					                   /* tp_as_number */
	0,					                   /* tp_as_sequence */
	0,		       			                   /* tp_as_mapping */
	0,					                   /* tp_hash */
	0,					                   /* tp_call */
	0,					                   /* tp_str */
	0,					                   /* tp_getattro */
	0,					                   /* tp_setattro */
	0,					                   /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC|Py_TPFLAGS_BASETYPE, /* tp_flags */
 	0,					                   /* tp_doc */
	0,					                   /* tp_traverse */
 	0,					                   /* tp_clear */
	0,					                   /* tp_richcompare */
	0,					                   /* tp_weaklistoffset */
	0,					                   /* tp_iter */
	0,					                   /* tp_iternext */
	0,					                   /* tp_methods */
	0,					                   /* tp_members */
	XmlParserMeta__getsets,				           /* tp_getset */
	0,					                   /* tp_base */
	0,					                   /* tp_dict */
	0,	                                                   /* tp_descr_get */
	0,  		                                           /* tp_descr_set */
	0,					                   /* tp_dictoffset */
	0,					                   /* tp_init */
	0,					                   /* tp_alloc */
	0,					                   /* tp_new */
	0,               			                   /* tp_free */
        0,                                                         /* tp_is_gc */
        0,                                                         /* tp_bases */
        0,                                                         /* tp_mro */
        0,                                                         /* tp_cache */
        0,                                                         /* tp_subclasses */
        0,                                                         /* tp_weaklist */
        0                                                          /* tp_del */
};

static void
PyXmlParserIter__tp_clear(PyXmlParserIter *self)
{
    Py_CLEAR(self->container);
}

static int
PyXmlParserIter__tp_traverse(PyXmlParserIter *self, visitproc visit, void *arg)
{
    Py_VISIT((PyObject *) self->container);
    return 0;
}

static void
PyXmlParserIter__tp_dealloc(PyXmlParserIter *self)
{
    Py_CLEAR(self->container);

    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
PyXmlParserIter__tp_iter(PyXmlParserIter *self)
{
    Py_INCREF(self);
    return (PyObject *) self;
}

static PyObject *
PyXmlParserIter__tp_iternext(PyXmlParserIter *self)
{
    xml::parser::event_type retval;

    try {

        retval = self->container->obj->next();

    } catch (xml::parsing const &exc) {

        PyErr_SetString((PyObject *) PyXmlParsingError_Type, exc.what());

        return NULL;
    }

    if (retval == xml::parser::event_type::eof) {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return PyLong_FromLong(retval);
}

PyTypeObject PyXmlParserIter_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "studxml.ParserIter",                                 /* tp_name */
    sizeof(PyXmlParserIter),                                       /* tp_basicsize */
    0,                                                             /* tp_itemsize */
    /* methods */
    (destructor)PyXmlParserIter__tp_dealloc,                       /* tp_dealloc */
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
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_GC,                         /* tp_flags */
    NULL,                                                          /* Documentation string */
    (traverseproc)PyXmlParserIter__tp_traverse,                    /* tp_traverse */
    (inquiry)PyXmlParserIter__tp_clear,                            /* tp_clear */
    (richcmpfunc)NULL,                                             /* tp_richcompare */
    0,                                                             /* tp_weaklistoffset */
    (getiterfunc)PyXmlParserIter__tp_iter,                         /* tp_iter */
    (iternextfunc)PyXmlParserIter__tp_iternext,                    /* tp_iternext */
    (struct PyMethodDef*)NULL,                                     /* tp_methods */
    (struct PyMemberDef*)0,                                        /* tp_members */
    NULL,                                                          /* tp_getset */
    NULL,                                                          /* tp_base */
    NULL,                                                          /* tp_dict */
    (descrgetfunc)NULL,                                            /* tp_descr_get */
    (descrsetfunc)NULL,                                            /* tp_descr_set */
    0,                                                             /* tp_dictoffset */
    (initproc)NULL,                                                /* tp_init */
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

