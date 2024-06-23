#include "XML_TreeStructure.h"
#include <iostream>
using namespace std;

XML_TreeStructure::XML_TreeStructure(const String& type, const String& id,
    const String& textContent, XML_TreeStructure* parent) {
    this->type = type;
    this->id = id;
    this->textContent = textContent;
}
bool XML_TreeStructure::addChild(const XML_TreeStructure& el) {
    XML_TreeStructure* child = new XML_TreeStructure(el);
    return this->ChildNodes.Add(child);
}
bool XML_TreeStructure::removeChild(const String& id) {
    for (int i = 0; i < ChildNodes.getSize(); i++) {
        if (ChildNodes[i]->id == id) {
            freeElement(ChildNodes[i]);
            ChildNodes.removeByIndex(i);
            return true;
        }
    }
    return false;
}
bool XML_TreeStructure::removeDescendant(const String& id, XML_TreeStructure* el) {
    for (int i = 0; i < el->ChildNodes.getSize(); i++) {
        if (el->ChildNodes[i]->getId() == id) {
            el->ChildNodes.removeByIndex(i);
            return true;
        }
        else if (removeDescendant(id, el->ChildNodes[i])) {
            return true;
        }
    }
    return false;
}
bool XML_TreeStructure::setTextContent(const String& textContent) {
    this->textContent = textContent;
    return true;
}
bool XML_TreeStructure::setId(const String& id) {
    this->id = id;
    return true;
}
bool XML_TreeStructure::setType(const String& type) {
    this->type = type;
    return true;
}
bool XML_TreeStructure::setAttribute(const String& key, const String& value) {
    return Attributes.setValue(key, value);
}
bool XML_TreeStructure::hasAttribute(const String& key, const String& value) const {
    try {
        if (value == String()) {
            return Attributes.hasKey(key);
        }
        else {
            return Attributes.find(key) == value;
        }
    }
    catch (const String& str) {
        return false;
    }
}
bool XML_TreeStructure::hasChild(const String& id) const {
    for (int i = 0; i < ChildNodes.getSize(); i++) {
        if (ChildNodes[i]->id == id) return true;
    }
    return false;
}
Array<const XML_TreeStructure*> XML_TreeStructure::getChildrenByAttribute(const String& key, const String& value) const {
    Array<const XML_TreeStructure*> res;
    for (int i = 0; i < ChildNodes.getSize(); i++) {
        if (ChildNodes[i]->hasAttribute(key, value)) {
            res.Add(ChildNodes[i]);
        }
    }
    return res;
}
Array<const XML_TreeStructure*> XML_TreeStructure::getChildrenByIndex(int index) const {
    Array<const XML_TreeStructure*> res;
    if (index < 0 || index >= ChildNodes.getSize()) return res;
    res.Add(ChildNodes[index]);
    return res;
}
Array<const XML_TreeStructure*> XML_TreeStructure::getChildrenByType(const String& type) const {
    Array<const XML_TreeStructure*> res;
    for (int i = 0; i < ChildNodes.getSize(); i++) {
        if (ChildNodes[i]->getType() == type) {
            res.Add(ChildNodes[i]);
        }
    }
    return res;
}
Array<const XML_TreeStructure*> XML_TreeStructure::getDescendants(const XML_TreeStructure* current) const {
    Array<const XML_TreeStructure*> res;
    for (int i = 0; i < current->getChildren().getSize(); i++) {
        res.Add(current->getChildren()[i]);
        res += getDescendants(current->getChildren()[i]);
    }
    return res;
}
bool XML_TreeStructure::removeAttribute(const String& key) {
    return Attributes.remove(key);
}
const XML_TreeStructure* XML_TreeStructure::getChild(int index) const {
    if (index < 0 || index >= ChildNodes.getSize())
        throw String("Invalid index");
    return ChildNodes[index];
}
Array<XML_TreeStructure*> XML_TreeStructure::getChildren() {
    return ChildNodes;
}
Array<const XML_TreeStructure*> XML_TreeStructure::getChildren() const {
    Array<const XML_TreeStructure*> res;
    for (int i = 0; i < ChildNodes.getSize(); i++) {
        res.Add(ChildNodes[i]);
    }
    return res;
}
const XML_TreeStructure* XML_TreeStructure::getLastChild() const {
    if (ChildNodes.getSize() == 0) return nullptr;
    return ChildNodes[ChildNodes.getSize() - 1];
}
const String& XML_TreeStructure::getText() const {
    return textContent;
}
void XML_TreeStructure::saveInFile(std::ostream& os, int k) const {
    for (int i = 0; i < k; i++) {
        os << "\t";
    }
    os << "<" << type;
    if (!id.Starts("def")) { 
        os << " id=\"" << id << "\"";
    }
    for (int i = 0; i < Attributes.getSize(); i++) {
        if (Attributes.getMyPairs()[i].key != "id") {
            os << " " << Attributes.getMyPairs()[i].key << "="   << "\"" << Attributes.getMyPairs()[i].value << "\"";
        }
    }
    os << ">";
    os << textContent;
    if (!this->ChildNodes.isEmpty()) {
        os << endl; 
    }
    for (int i = 0; i < this->ChildNodes.getSize(); i++) {
        this->ChildNodes[i]->saveInFile(os, k + 1);
    }
    if (!this->ChildNodes.isEmpty()) for (int i = 0; i < k; i++) {
        os << "\t";
    }
    os << "</" << type << ">" << endl;
}
void XML_TreeStructure::print(std::ostream& os, int k) const {
    for (int i = 0; i < k; i++) {
        os << "\t";
    }
    os << "<" << type;
    os << " id=\"" << id << "\"";
    for (int i = 0; i < Attributes.getSize(); i++) {
        if (Attributes.getMyPairs()[i].key != "id"){ 
            os << " " << Attributes.getMyPairs()[i].key << "=" << "\"" << Attributes.getMyPairs()[i].value << "\"";
        }
    }
    os << ">";
    os << textContent;
    if (!this->ChildNodes.isEmpty()) { 
        os << endl;
    }
    for (int i = 0; i < this->ChildNodes.getSize(); i++) {
        this->ChildNodes[i]->print(os, k + 1);
    }
    if (!this->ChildNodes.isEmpty()) for (int i = 0; i < k; i++) {
        os << "\t";
    }
    os << "</" << type << ">" << endl;
}

const MyMap<String, String>& XML_TreeStructure::getAttributes() const {
    return Attributes;
}


void freeElement(XML_TreeStructure* el) {
    for (int i = 0; i < el->ChildNodes.getSize(); i++) {
        freeElement(el->ChildNodes[i]);
    }
    delete el;
}

const String& XML_TreeStructure::getType() const {
    return type;
}
const String& XML_TreeStructure::getId() const {
    return id;
}
