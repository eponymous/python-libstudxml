# Python wrapper for libstudxml

Includes [libstudxml](http://www.codesynthesis.com/projects/libstudxml/) as a submodule in the source tree.

### Building

Can't figure out the wonky build2 system so...
```
touch libstudxml/libstudxml/version.hxx

python3 setup.py build
```
builds everything (libstudxml and the python bindings) as a python module.

NOTE: needs to work around using io.IOBase to support python 2

### Roundtrip Example

Reading from a python string object and outputting to sys.sysout

```python
import studxml as xml
import sys

position = '''
<object id="123">
  <name>Lion's Head</name>
  <type>mountain</type>
  <position lat="-33.8569" lon="18.5083"/>
  <position lat="-33.8568" lon="18.5083"/>
  <position lat="-33.8568" lon="18.5082"/>
</object>
'''

p = xml.Parser(position, 'position.xml', xml.Parser.receive_default | xml.Parser.receive_attributes_event)
s = xml.Serializer(sys.stdout, 'position.xml', 2)

p.content = xml.content.complex

for event in p:
    if event == xml.Parser.start_element:
        s.start_element(p.qname)
    elif event == xml.Parser.end_element:
        s.end_element(p.qname)
    elif event == xml.Parser.start_namespace_decl:
        s.namespace_decl(p.namespace, p.prefix)
    elif event == xml.Parser.end_namespace_decl:
        pass
    elif event == xml.Parser.start_attribute:
        s.start_attribute(p.qname)
    elif event == xml.Parser.end_attribute:
        s.end_attribute(p.qname)
    elif event == xml.Parser.characters:
        s.characters(p.value.strip())
    elif event == xml.Parser.eof:
        pass
```

### Processing Example

Reading from a python file object and printing the result

```python
import studxml as xml

with open('libstudxml/examples/processing/position.xml', 'rb') as f:
    p = xml.Parser(f, 'position.xml')

    p.next_expect(p.start_element, "object", xml.content.complex)

    print("id: ", p.attribute("id"))
    print("name: ", p.element("name"))
    print("type: ", p.element("type"))

    while 1:
        p.next_expect(p.start_element, "position", xml.content.empty)

        print("%s: lat:%s long:%s" % (p.qname, p.attribute("lat"), p.attribute("lon")))

        p.next_expect (p.end_element)

        if p.peek() != p.start_element:
            break
```
