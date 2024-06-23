#include "XML_TreeHandler.h"
#include <iostream>
#include <fstream>
using namespace std;

XML_TreeHandler::XML_TreeHandler() {
    this->root = new XML_TreeStructure("root", "rootId");
}
XML_TreeHandler::~XML_TreeHandler() {
    freeElement(root);
}
const XML_TreeStructure* XML_TreeHandler::getRoot() const {
    return root;
}

bool XML_TreeHandler::hasElementWithId(const String& id) const {
    return ids.hasKey(id);
}

void XML_TreeHandler::saveInFile(const String& FileName) const {
    ofstream file(FileName.c_str());
    for (int i = 0; i < root->getChildren().getSize(); i++) {
        root->getChildren()[i]->saveInFile(file);
    }
}

void XML_TreeHandler::print() const {
    for (int i = 0; i < root->getChildren().getSize(); i++) {
        root->getChildren()[i]->print(cout);
    }
}
const XML_TreeStructure* XML_TreeHandler::getElementById(const String& id, const XML_TreeStructure* el) const {
    if (el->getId() == id) return el;
    for (int i = 0; i < el->getChildren().getSize(); i++) {
        const XML_TreeStructure* res = getElementById(id, el->getChildren()[i]);
        if (res != nullptr) {
            return res;
        }
    }
    return nullptr;
}
XML_TreeStructure* XML_TreeHandler::getElementById(const String& id, XML_TreeStructure* el) {
    if (el->getId() == id) return el;
    for (int i = 0; i < el->getChildren().getSize(); i++) {
        XML_TreeStructure* res = getElementById(id, el->getChildren()[i]);
        if (res != nullptr) {
            return res;
        }
    }
    return nullptr;
}
bool XML_TreeHandler::printAttribute(const String& id, const String& key) const {
    const XML_TreeStructure* el = getElementById(id, root);
    if (el == nullptr) { 
        return false;
    }
    cout << el->getAttributes().find(key);
    return true;
}
void XML_TreeHandler::setAttribute(const String& id,
    const String& key, const String& value) {
    XML_TreeStructure* el = getElementById(id, root);
    if (el == nullptr) {
        throw String("There is no such element");
    }
    el->setAttribute(key, value);
}
void XML_TreeHandler::printChildren(const String& id) const {
    const XML_TreeStructure* el = getElementById(id, root);
    if (el == nullptr) return;
    if (el->getChildren().getSize() == 0) {
        cout << "There are no ChildNodes of node with id " << id << endl;
    }
    for (int i = 0; i < el->getChildren().getSize(); i++) {
        el->getChildren()[i]->print(cout);
    }
}
const XML_TreeStructure* XML_TreeHandler::getChildByIndex(const String& id, int index) const {
    const XML_TreeStructure* el = getElementById(id, root);
    if (el == nullptr) {
        throw String("There is no such element");
    }
    return getElementById(id, root)->getChildren()[index];
}
const XML_TreeStructure* XML_TreeHandler::getLastChild(const String& id) const {
    const XML_TreeStructure* el = getElementById(id, root);
    if (el == nullptr) {
        throw String("There is no such element");
    }
    const XML_TreeStructure* res = el->getLastChild();
    if (res == nullptr) {
        throw String("Element has no ChildNodes");
    }
    return el->getLastChild();
}
bool XML_TreeHandler::deleteAttribute(const String& id, const String& key) {
    XML_TreeStructure* el = getElementById(id, root);
    if (el == nullptr) {
        throw String("There is no such element");
    }
    return el->removeAttribute(key);
}
void XML_TreeHandler::addChild(const String& id, const XML_TreeStructure& el) {
        XML_TreeStructure* parent = getElementById(id, root);
        try {
        if (parent == nullptr) {
            throw String("There is no such element");
             }
        }
        catch (const String& errorMessage) {
            ErrorHandler::getInstance().logError(errorMessage);
        }
        String idToBeAdded = el.getId();
        XML_TreeStructure elToBeAdded = el;
        if (idToBeAdded == "def") {
            idToBeAdded = parent->getId().concat("_").concat(String(countOfElements));
        }
        countOfElements++;
        elToBeAdded.setId(idToBeAdded);
        parent->addChild(elToBeAdded);
        ids.add(idToBeAdded, parent->getChildren()[parent->getChildren().getSize() - 1]);
}
   

const XML_TreeStructure* XML_TreeHandler::getParent(const String& id) const {
    try {
        for (int i = 0; i < ids.getSize(); i++) {
            if (ids.getMyPairs()[i].value->hasChild(id)) {
                return ids.getMyPairs()[i].value;
            }
        }
        throw String("There is no such element");
    }
    catch (const String& errorMessage) {
        ErrorHandler::getInstance().logError(errorMessage);
    }
}

const XML_TreeStructure* XML_TreeHandler::getElement(const String& id) const {
    return getElementById(id, root);
}
void XML_TreeHandler::clear() {
    freeElement(root);
    root = new XML_TreeStructure("wrapper", "rootId");
    ids.clear();
    countOfElements = 0;
}


Array<const XML_TreeStructure*> XML_TreeHandler::getElementsByTagName(const String& tagName) const {
    Array<const XML_TreeStructure*> list;
    for (int i = 0; i < ids.getSize(); i++) {
        if (ids.getMyPairs()[i].value->getType() == tagName) {
            list.Add(ids.getMyPairs()[i].value);
        }
    }
    return list;
}

Array<const XML_TreeStructure*> XML_TreeHandler::getElementsByAttribute(const String& attribute, const String& value) const {
    Array<const XML_TreeStructure*> list;
    for (int i = 0; i < ids.getSize(); i++) {
        if (value == String()) {
            if (ids.getMyPairs()[i].value->getAttributes().hasKey(attribute)) {
                list.Add(ids.getMyPairs()[i].value);
            }
            else if (ids.getMyPairs()[i].value->getAttributes().hasKey(attribute) && ids.getMyPairs()[i].value->getAttributes().find(attribute) == value) {
                list.Add(ids.getMyPairs()[i].value);
            }
        }
    }
    return list;
}

