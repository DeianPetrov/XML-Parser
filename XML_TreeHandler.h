#pragma once
#include "Array.hpp"
#include "XML_TreeStructure.h"
#include "MyMap.hpp"
#include "MyString.h"
#include "ErrorHandler.h"
class XML_TreeHandler
{
    XML_TreeStructure* root;
    unsigned countOfElements = 0;
    MyMap<String, const XML_TreeStructure*> ids;
    XML_TreeStructure* getElementById(const String& id, XML_TreeStructure*);
    const XML_TreeStructure* getElementById(const String& id, const XML_TreeStructure*) const;
public:
    XML_TreeHandler();
    XML_TreeHandler(const XML_TreeHandler&) = delete;
    XML_TreeHandler& operator=(const XML_TreeHandler&) = delete;
    ~XML_TreeHandler();
    const XML_TreeStructure* getRoot() const;
    bool hasElementWithId(const String& id) const;
    void saveInFile(const String& FileName) const;
    void print() const;
    bool printAttribute(const String& id, const String& key) const;
    void setAttribute(const String& id, const String& key, const String& value);
    void printChildren(const String& id) const;
    const XML_TreeStructure* getChildByIndex(const String& id, int index) const;
    const XML_TreeStructure* getLastChild(const String& id) const;
    const XML_TreeStructure* getParent(const String& id) const;
    bool deleteAttribute(const String& id, const String& key);
    void addChild(const String& id, const XML_TreeStructure& el);
    const XML_TreeStructure* getElement(const String& id) const;
    Array<const XML_TreeStructure*> getElementsByTagName(const String& tagName) const;
    Array<const XML_TreeStructure*> getElementsByAttribute(const String& attribute, const String& value = String()) const;
    void clear();
};

