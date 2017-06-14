from distutils.core import setup, Extension

studxml_module = Extension('studxml',
                           include_dirs=['.',
                                         'libstudxml/',
                                         'libstudxml/libstudxml/details/',
                                         'libstudxml/libstudxml/details/expat/',
                                         'libstudxml/libstudxml/details/genx/',
                                         '/usr/include/'],
                           sources = ['py_parser.cpp',
                                      'py_serializer.cpp',
                                      'py_qname.cpp',
                                      'py_studxml.cpp',
                                      'libstudxml/libstudxml/details/expat/xmlparse.c',
                                      'libstudxml/libstudxml/details/expat/xmlrole.c',
                                      'libstudxml/libstudxml/details/expat/xmltok.c',
                                      'libstudxml/libstudxml/details/expat/xmltok_impl.c',
                                      'libstudxml/libstudxml/details/expat/xmltok_ns.c',
                                      'libstudxml/libstudxml/details/genx/char-props.c',
                                      'libstudxml/libstudxml/details/genx/genx.c',
                                      'libstudxml/libstudxml/parser.cxx',
                                      'libstudxml/libstudxml/qname.cxx',
                                      'libstudxml/libstudxml/serializer.cxx',
                                      'libstudxml/libstudxml/value-traits.cxx'])

setup(name='studxml',
      version="0.1",
      description='libstudxml python bindings',
      author='Dan Eicher',
      author_email='dan@eu.phorio.us',
      ext_modules=[studxml_module])

