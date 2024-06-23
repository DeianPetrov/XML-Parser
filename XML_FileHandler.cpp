#include "XML_FileHandler.h"
#include <fstream>
#include <iostream>
using namespace std;

XML_FileHandler::XML_FileHandler()
{
    this->FileName = "";
}

XML_FileHandler::XML_FileHandler(const String& FileName) {
    this->FileName = FileName;
    loadBuffer();
}

void XML_FileHandler::setFileName(const String& FileName) {
    this->FileName = FileName;
}

bool XML_FileHandler::fileIsOpened() const {
    return FileName != String();
}

void XML_FileHandler::loadBuffer() {
    if (FileName == String()) {
        Buffer = String();
        return;
    }
    ifstream file(FileName.c_str());
    if (!file.is_open()) {
        Buffer = String();
        return;
    }
    while (!file.eof()) {
        if (file.peek() != '\t' && file.peek() != '\n') {
            char buffer[2];
            buffer[0] = file.get();
            buffer[1] = '\0';
            Buffer += buffer;
        }
        else file.get();
    }

    minify();
}

const String& XML_FileHandler::getFileName() const {
    return FileName;
}


void XML_FileHandler::minify() {
    String minifiedContent;
    int iter = 0;
    while (iter < Buffer.getLength()) {
        if (Buffer.subStr(iter).Starts("  ")) {
            bool StartsSpecialSymbol = Buffer[iter - 1] == '<'
                || Buffer[iter - 1] == '/'
                || Buffer[iter - 1] == '=';
            while (Buffer[iter] == ' ') {
                iter++;
            }
            bool EndsSpecialSymbol = Buffer[iter] == '<'
                || Buffer[iter] == '/'
                || Buffer[iter] == '>'
                || Buffer[iter] == '=';
            if (!StartsSpecialSymbol && !EndsSpecialSymbol) {
                minifiedContent += " ";

            }
            else if (Buffer[iter] == ' ') {
                bool StartsSpecialSymbol = Buffer[iter - 1] == '<'
                    || Buffer[iter - 1] == '/'
                    || Buffer[iter - 1] == '=';

                bool endWithSpecialSymbol =
                    (Buffer.charAt(iter + 1) == '<'
                        || Buffer.charAt(iter + 1) == '/'
                        || Buffer.charAt(iter + 1) == '=');
                if (StartsSpecialSymbol || endWithSpecialSymbol) {
                    iter++;
                }
                else {
                    minifiedContent += Buffer.charAt(iter++);
                }
            }
            else {
                minifiedContent += Buffer.charAt(iter++);
            }
        }
        minifiedContent = minifiedContent.trim();
        Buffer = minifiedContent.subStr(0, minifiedContent.getLength() - 1);
    }
}
void XML_FileHandler::parseNodeByTagInfo(const String& tagInfo, XML_TreeStructure& node) const {
    int startIndex = tagInfo.IndexOf(" ");
    String type = tagInfo.subStr(0, startIndex);
    node.setType(type);
    bool isInParenthesis = false;
    for (int i = (startIndex++) + 1; i < tagInfo.getLength(); i++) {
        if (!isInParenthesis && tagInfo[i] == '\"') {
            isInParenthesis = true;
        }
        else if (isInParenthesis && tagInfo[i] == '\"') {
            String attributeStr = tagInfo.subStr(startIndex, i);
            Array<String> attributeData = attributeStr.split("=\"");
            node.setAttribute(attributeData[0], attributeData[1]);
            if (attributeData[0] == "id") {
                node.setId(attributeData[1]);
            }
            startIndex = i + 2;
            isInParenthesis = false;
        }
    }
}

void XML_FileHandler::parse(const String& elementTextContent, XML_TreeHandler& tree, const XML_TreeStructure* parent, int& iter) const {
    String tagInfo;
    int searchingStartingIndex = iter;
    try {
        while (elementTextContent[iter] != '>') {
            tagInfo += elementTextContent[iter];
            iter++;
            if (iter >= elementTextContent.getLength() || elementTextContent[iter] == '<')
                throw String("Parsing error! 1 ");

        }
        XML_TreeStructure node;
        parseNodeByTagInfo(tagInfo, node);
        iter++;
        String textContent;
        searchingStartingIndex = iter;
        while (elementTextContent[iter] != '<') {
            textContent += elementTextContent[iter];
            iter++;
            if (iter >= elementTextContent.getLength() || elementTextContent[iter] == '>')
                throw String("Parsing error! 2 ");
        }
        node.setTextContent(textContent);
        tree.addChild(parent->getId(), node);
        iter++;
        if (elementTextContent[iter] != '/')
            parse(elementTextContent, tree, tree.getLastChild(parent->getId()), iter);
        searchingStartingIndex = iter;
        while (elementTextContent[iter] != '>') {
            iter++;
            if (iter >= elementTextContent.getLength() || elementTextContent[iter] == '<')
                throw String("Parsing error! 3 ");

        }
        iter++;
        iter++;
        if (elementTextContent[iter] != 0 && elementTextContent[iter] != '/')
            parse(elementTextContent, tree, parent, iter);
    }
    catch (const String& errorMessage) {
        ErrorHandler::getInstance().logError(errorMessage);
    }
}

void XML_FileHandler::parseTree(XML_TreeHandler& tree) const {
    if (Buffer.getLength() <= 1) return;
    int iter = 0;
    parse(Buffer.subStr(1), tree, tree.getRoot(), iter);
}