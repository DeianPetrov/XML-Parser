#pragma once
#include "Array.hpp"
#include "MyMap.hpp"
#include "MyString.h"
#include <iostream>

const String DEFAULT_ID = "def";
const String DEFAULT_TEXT_CONTENT = "";
const String DEFAULT_TYPE = "type";

class XML_TreeStructure {
   
public:
    XML_TreeStructure(const String& type = DEFAULT_TYPE, const String& id = DEFAULT_ID,
        const String& textContent = DEFAULT_TEXT_CONTENT, XML_TreeStructure* parent = nullptr);
    bool addChild(const XML_TreeStructure& el);
    bool setTextContent(const String& textContent);
    bool setId(const String& id);
    bool setType(const String&);
    bool removeChild(const String& id);
    static bool removeDescendant(const String& id, XML_TreeStructure*);
    bool setAttribute(const String& key, const String& value);
    bool hasAttribute(const String& key, const String& value = String()) const;
    bool hasChild(const String& id) const;
    Array<const XML_TreeStructure*> getChildrenByType(const String& type) const;
    Array<const XML_TreeStructure*> getChildrenByAttribute(const String& key, const String& value = String()) const;
    Array<const XML_TreeStructure*> getChildrenByIndex(int index) const;
    Array<const XML_TreeStructure*> getDescendants(const XML_TreeStructure* el) const;
    bool removeAttribute(const String& key);
    const XML_TreeStructure* getChild(int index) const;
    Array<XML_TreeStructure*> getChildren();
    Array<const XML_TreeStructure*> getChildren() const;
    const XML_TreeStructure* getLastChild() const;
    const String& getText() const;
    const String& getId() const;
    const MyMap<String, String>& getAttributes() const;
    const String& getType() const;
    void saveInFile(std::ostream& os, int k = 0) const;
    void print(std::ostream& os, int k = 0) const;
    friend void freeElement(XML_TreeStructure*);
private:
    String type;
    String id;
    String textContent;
    Array<XML_TreeStructure*> ChildNodes;
    MyMap<String, String> Attributes;
};


