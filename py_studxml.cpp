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

PyTypeObject *PyXmlParsingError_Type;
PyTypeObject *PyXmlSerializationError_Type;

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef studxml_content_moduledef = {
    PyModuleDef_HEAD_INIT,
    "studxml.content",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initstudxml_content(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&studxml_content_moduledef);
    #else
    m = Py_InitModule3((char *) "studxml.content", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "empty", xml::content::empty);
    PyModule_AddIntConstant(m, (char *) "simple", xml::content::simple);
    PyModule_AddIntConstant(m, (char *) "complex", xml::content::complex);
    PyModule_AddIntConstant(m, (char *) "mixed", xml::content::mixed);
    return m;
}

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef studxml_moduledef = {
    PyModuleDef_HEAD_INIT,
    "studxml",
    NULL,
    -1,
    NULL,
};
#endif

#if PY_VERSION_HEX >= 0x03000000
    #define MOD_ERROR NULL
    #define MOD_INIT(name) PyObject * PyInit_##name(void)
    #define MOD_RETURN(val) val
#else
    #define MOD_ERROR
    #define MOD_INIT(name) void init##name(void)
    #define MOD_RETURN(val)
#endif
#if defined(__cplusplus)
extern "C"
#endif
#if defined(__GNUC__) && __GNUC__ >= 4
__attribute__ ((visibility("default")))
#endif

MOD_INIT(studxml)
{
    PyObject *tmp_value, *submodule, *m;

    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&studxml_moduledef);
    #else
    m = Py_InitModule3((char *) "studxml", NULL, NULL);
    #endif

    if (m == NULL) {
        return MOD_ERROR;
    }

    /* Register the 'xml::parser' class */
    PyXmlParserMeta_Type.tp_base = Py_TYPE(&PyBaseObject_Type);
    /* Some fields need to be manually inheritted from the parent metaclass */
    PyXmlParserMeta_Type.tp_traverse = Py_TYPE(&PyBaseObject_Type)->tp_traverse;
    PyXmlParserMeta_Type.tp_clear = Py_TYPE(&PyBaseObject_Type)->tp_clear;
    PyXmlParserMeta_Type.tp_is_gc = Py_TYPE(&PyBaseObject_Type)->tp_is_gc;
    /* PyType tp_setattro is too restrictive */
    PyXmlParserMeta_Type.tp_setattro = PyObject_GenericSetAttr;

    PyType_Ready(&PyXmlParserMeta_Type);

    Py_TYPE(&PyXmlParser_Type) = &PyXmlParserMeta_Type;

    if (PyType_Ready(&PyXmlParser_Type)) {
        return MOD_ERROR;
    }

    PyModule_AddObject(m, (char *) "Parser", (PyObject *) &PyXmlParser_Type);

    /* Register the 'xml::serializer' class */
    if (PyType_Ready(&PyXmlSerializer_Type)) {
        return MOD_ERROR;
    }

    PyModule_AddObject(m, (char *) "Serializer", (PyObject *) &PyXmlSerializer_Type);

    /* Register the 'xml::qname' class */
    if (PyType_Ready(&PyXmlQname_Type)) {
        return MOD_ERROR;
    }

    PyModule_AddObject(m, (char *) "Qname", (PyObject *) &PyXmlQname_Type);

    if (PyType_Ready(&PyXmlParserIter_Type)) {
        return MOD_ERROR;
    }

    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, (char *) "ParserIter", (PyObject *) &PyXmlParserIter_Type);

    /* Register the 'xml::parsing' exception */
    if ((PyXmlParsingError_Type = (PyTypeObject*) PyErr_NewException((char*)"studxml.ParsingError", NULL, NULL)) == NULL) {
        return MOD_ERROR;
    }

    Py_INCREF((PyObject *) PyXmlParsingError_Type);

    PyModule_AddObject(m, (char *) "ParsingError", (PyObject *) PyXmlParsingError_Type);

    /* Register the 'xml::serialization' exception */
    if ((PyXmlSerializationError_Type = (PyTypeObject*) PyErr_NewException((char*)"studxml.SerializationError", NULL, NULL)) == NULL) {
        return MOD_ERROR;
    }

    Py_INCREF((PyObject *) PyXmlSerializationError_Type);

    PyModule_AddObject(m, (char *) "SerializationError", (PyObject *) PyXmlSerializationError_Type);

     // xml::parser::start_element
    tmp_value = PyLong_FromLong(xml::parser::start_element);
    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, "start_element", tmp_value);
    Py_DECREF(tmp_value);

     // xml::parser::end_element
    tmp_value = PyLong_FromLong(xml::parser::end_element);
    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, "end_element", tmp_value);
    Py_DECREF(tmp_value);

     // xml::parser::start_attribute
    tmp_value = PyLong_FromLong(xml::parser::start_attribute);
    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, "start_attribute", tmp_value);
    Py_DECREF(tmp_value);

     // xml::parser::end_attribute
    tmp_value = PyLong_FromLong(xml::parser::end_attribute);
    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, "end_attribute", tmp_value);
    Py_DECREF(tmp_value);

     // xml::parser::characters
    tmp_value = PyLong_FromLong(xml::parser::characters);
    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, "characters", tmp_value);
    Py_DECREF(tmp_value);

     // xml::parser::start_namespace_decl
    tmp_value = PyLong_FromLong(xml::parser::start_namespace_decl);
    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, "start_namespace_decl", tmp_value);
    Py_DECREF(tmp_value);

     // xml::parser::end_namespace_decl
    tmp_value = PyLong_FromLong(xml::parser::end_namespace_decl);
    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, "end_namespace_decl", tmp_value);
    Py_DECREF(tmp_value);

     // xml::parser::eof
    tmp_value = PyLong_FromLong(xml::parser::eof);
    PyDict_SetItemString((PyObject *) PyXmlParser_Type.tp_dict, "eof", tmp_value);
    Py_DECREF(tmp_value);

    submodule = initstudxml_content();

    if (submodule == NULL) {
        return MOD_ERROR;
    }

    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "content", submodule);

    return MOD_RETURN(m);
}

