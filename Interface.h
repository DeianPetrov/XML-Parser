#pragma once
#include "MyMap.hpp"
#include "Array.hpp"
#include "MyString.h"
#include "XML_TreeStructure.h"
#include "XML_FileHandler.h"
#include <iostream>
class Interface {
public:
    //static  Interface instance;
    void Run();
private:
    XML_FileHandler parser;
    XML_TreeHandler tree;
    bool hasChanged = false;
    void openFile(const String&);
    void closeFile();
    void saveFile();
    void saveAs(const String&);
    void help();
    bool exit(bool& flag);
    void print();
    void printAttribute(const String& id,
        const String& key);
    void setAttribute(const String& id, const String& key,
        const String& value);
    void printChildren(const String& id);
    void printChildByIndex(const String& id, int index);
    void printText(const String& id);
    void removeAttribute(const String& id, const String& key);
    void addChild(const String& id, const String& type);
    void xmlPath(const String& xmlPath);
    bool fileIsOpened() const;
};


