#include "XML_XpathHandler.h"

Array<const XML_TreeStructure*> XML_XpathHandler::getElements(const String& xmlPath, const XML_TreeHandler& tree) {
    Array<String> parts = xmlPath.split("/");
    Array<const XML_TreeStructure*> elementsToFind;

    for (int i = 0; i < parts.getSize(); i++) {
        String part = parts[i];
        String tagName = extractTagName(part);

        if (i == 0) {
            elementsToFind = getInitialElements(tree, tagName);
        }
        else {
            elementsToFind = updateElements(elementsToFind, tagName);
        }

        if (part.Ends(")")) {
            elementsToFind = filterByAttribute(elementsToFind, part, extractAttributeData(part));
        }
        else if (part.Ends("]")) {
            elementsToFind = filterByIndex(elementsToFind, extractIndex(part));
        }
   
    }

    return elementsToFind;
}

int XML_XpathHandler::count(const String& xmlPath, const XML_TreeHandler& tree) {
    Array<const XML_TreeStructure*> elements = getElements(xmlPath, tree);
    return elements.getSize();
}


String XML_XpathHandler::extractTagName(const String& part) {
    int attributeIndexStart = part.IndexOf("(");
    int childIndexStart = part.IndexOf("[");
    int comparisonIndexStart = part.IndexOf("=");

    if (part.Ends(")")) {
        return part.subStr(0, attributeIndexStart);
    }
    else if (part.Ends("]")) {
        return part.subStr(0, childIndexStart);
    }
    else if (comparisonIndexStart != -1) {
        return part.subStr(0, comparisonIndexStart - 1);
    }
    else {
        return part;
    }
}

Array<const XML_TreeStructure*> XML_XpathHandler::getInitialElements(const XML_TreeHandler& tree, const String& tagName) {
    if (!tagName.Starts("/*")) {// to check
        return tree.getElementsByTagName(tagName);
    }
    else {
        return tree.getRoot()->getChildren()[0]->getChildrenByType(tagName.subStr(1, tagName.getLength()));
    }
}

Array<const XML_TreeStructure*> XML_XpathHandler::updateElements(const Array<const XML_TreeStructure*>& elements, const String& tagName) {
    Array<const XML_TreeStructure*> updatedElements;

    for (int j = 0; j < elements.getSize(); j++) {
        if (tagName == "*") {
            updatedElements += elements[j]->getChildren();
        }
        else {
            updatedElements += elements[j]->getChildrenByType(tagName);
        }
    }

    return updatedElements;
}

String XML_XpathHandler::extractAttributeData(const String& part) {
    int attributeIndexStart = part.IndexOf("(");
    return part.subStr(attributeIndexStart + 1, part.getLength() - 1);
}

Array<const XML_TreeStructure*> XML_XpathHandler::filterByAttribute(const Array<const XML_TreeStructure*>& elements, const String& part, const String& attributeData) {
    Array<const XML_TreeStructure*> updatedElements; 
        Array<String> MyPair = attributeData.split("=");
        for (int j = 0; j < elements.getSize(); j++) {
            if (elements[j]->hasAttribute(MyPair[0], MyPair[1])) {
                updatedElements += elements[j];
            }
        
        }

    return updatedElements;
}

String XML_XpathHandler::extractIndex(const String& part) {
    int childIndexStart = part.IndexOf("[");
    return part.subStr(childIndexStart + 1, part.getLength() - 1);
}

Array<const XML_TreeStructure*> XML_XpathHandler::filterByIndex(const Array<const XML_TreeStructure*>& elements, const String& index) {
    Array<const XML_TreeStructure*> updatedElements;
    int n = String::my_atoi(index);

    for (int j = 0; j < elements.getSize(); j++) {
        Array<const XML_TreeStructure*> ChildNodes = elements[j]->getChildrenByIndex(n);
        updatedElements += ChildNodes;
    }

    return updatedElements;
}