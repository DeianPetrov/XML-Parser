#pragma once
#include "XML_TreeHandler.h"
#include "XML_TreeStructure.h"
#include "MyString.h"
#include "ErrorHandler.h"
class XML_FileHandler {
    String FileName;
    String Buffer;
    void parse(const String& content, XML_TreeHandler&, const XML_TreeStructure*, int& iter) const;
    void loadBuffer();
    void minify();
    void parseNodeByTagInfo(const String&, XML_TreeStructure& node) const;
public:
    XML_FileHandler();
    XML_FileHandler(const String& FileName);
    void setFileName(const String& path);
    bool fileIsOpened() const;
    void parseTree(XML_TreeHandler&) const;
    const String& getFileName() const;
};


