#include "Interface.h"

void Interface::help() {
    std::cout << "The following commands are supported: " << std::endl;
    std::cout << "  open							   \topens <fileName>" << std::endl;
    std::cout << "  close                              \tcloses currently opened file" << std::endl;
    std::cout << "  save                               \tsaves the currently open file" << std::endl;
    std::cout << "  saveaAs							   \tsaves the currently open file in another given <filename>" << std::endl;
    std::cout << "  help                               \tprints this information" << std::endl;
    std::cout << "  exit                               \texits the program" << std::endl;
    std::cout << "  print                              \tprints the opened file" << std::endl;
    std::cout << "  select <id> <key>                  \tprints attribute to an element with <id> by key" << std::endl;
    std::cout << "  set <id> <key> <value>             \tsets attribute to an element with <id> by key and value" << std::endl;
    std::cout << "  ChildNodes <id>                      \tprints the Attributes of the nested elements" << std::endl;
    std::cout << "  child <id> <n>                     \tgives access to the n-th child of an element with <id>" << std::endl;
    std::cout << "  text <id>                          \tprints text of element with <id>" << std::endl;
    std::cout << "  delete <id> <key>                  \tremoves attribute <key> from element with <<<>" << std::endl;
    std::cout << "  newchild <id> <type>               \tcreates child element if <type> to element <id>" << std::endl;
    std::cout << "  xpath <xmlPath>                    \returns values based on XPath requests" << std::endl;
}
bool Interface::fileIsOpened() const {
    if (!parser.fileIsOpened()) {
        std::cout << "File hasn't been opened!" << std::endl;
        return false;
    }
    return true;
}
void Interface::openFile(const String& FileName) {
    if (!FileName.Ends(".xml")) {
        std::cout << "Wrong file format" << std::endl;
        return;
    }
    parser = XML_FileHandler(FileName);
    try {
        parser.parseTree(tree);
        std::cout << "Successfully opened " << FileName << std::endl;
    }
    catch (const String& str) {
        parser.setFileName("");
        std::cout << str << std::endl;
    }
}
void Interface::closeFile() {
    if (parser.getFileName() != String()) {
        parser.setFileName(String());
        tree.clear();
        std::cout << "Successfully closed file!" << std::endl;
        return;
    }
    std::cout << "File hasn't been opened!" << std::endl;
}
void Interface::saveFile() {
    tree.saveInFile(parser.getFileName());
    std::cout << "Successfully saved " << parser.getFileName() << std::endl;
    hasChanged = false;
}
void Interface::saveAs(const String& FileName) {
    tree.saveInFile(FileName);
    std::cout << "Successfully saved file in " << FileName << std::endl;
    hasChanged = false;
}

bool Interface::exit(bool& flag) {

    return flag = true;
}
void Interface::print() {
    tree.print();
}
void Interface::printAttribute(const String& id,
    const String& key) {
    try {
        bool res = tree.printAttribute(id, key);
        if (!res) std::cout << "There is no such attribute to element " << id << std::endl;
        std::cout << std::endl;
    }
    catch (const String& str) {
        std::cout << str << std::endl;
    }
}
void Interface::setAttribute(const String& id, const String& key,
    const String& value) {
    try {
        tree.setAttribute(id, key, value);
        hasChanged = true;
    }
    catch (const String& str) {
        std::cout << str << std::endl;
        return;
    }

    std::cout << "Successfully set attribute !"<<std::endl;
}
void Interface::printChildren(const String& id) {
    try {
        tree.printChildren(id);
    }
    catch (const String& errorMessage) {
        ErrorHandler::getInstance().logError(errorMessage);
    }
}
void Interface::printChildByIndex(const String& id, int pos) {
    try {
        const XML_TreeStructure* el = tree.getChildByIndex(id, pos);
        el->print(std::cout);
    }
    catch (const String& errorMessage) {
        ErrorHandler::getInstance().logError(errorMessage);
    }
}
void Interface::printText(const String& id) {
    const XML_TreeStructure* el = tree.getElement(id);
    if (el == nullptr) {
        std::cout << "There is no such element" << std::endl;
        return;
    }
    std::cout << el->getText() << std::endl;
}

void Interface::removeAttribute(const String& id, const String& key) {
    try {
        bool res = tree.deleteAttribute(id, key);
        if (res) std::cout << "Successfully removed attribute to an XML element" << std::endl;
        else std::cout << "Attribute removed unsuccessfully" << std::endl;
        hasChanged = true;
    }
    catch (const String& errorMessage) {
        ErrorHandler::getInstance().logError(errorMessage);
    }
}
void Interface::addChild(const String& id, const String& type) {
    XML_TreeStructure el(type, DEFAULT_ID);
    std::cout << "> Enter node text content (optional): ";
    String textContent;
    std::cin >> textContent;
    el.setTextContent(textContent);
    try {
        tree.addChild(id, el);
    }
    catch (const String& errorMessage) {
        ErrorHandler::getInstance().logError(errorMessage);
        return;
    }
    std::cout << "Successfully added child." << std::endl;
    hasChanged = true;
}

void Interface::xmlPath(const String& xmlPath) {
    std::cout << "THIS FUNCIONALITY IS STILL UNDER CONSTRUCTION" << std::endl;
    return;
}

void Interface::Run() {
    
    bool quit = false;
    String input;
    String file,key,value,ID;
    while (quit != true) {
        std::cout << "Enter your command input: ";
        std::cin >> input;
            Array<String> parts = input.split(" ");
            String command = parts[0].toUpperCase();
            if (command.equals("OPEN")) {
                std::cout << "Enter the name of the file : ";
                std::cin >> file;
                openFile(file);
            }
            else if (command.equals("CLOSE")) {
                if (fileIsOpened()) closeFile();
            }
            else if (command.equals("SAVE")) {
                if (fileIsOpened()) saveFile();
            }
            else if (command.equals("SAVEAS")) {
                String otherfile;
                std::cout << "Enter the name of the file : ";
                std::cin >> otherfile;
                if (fileIsOpened()) saveAs(otherfile);
            }
            else if (command.equals("HELP")) {
                help();
            }
            else if (command.equals("EXIT")) {
                exit(quit);
                std::cout << "Exiting is successful!" << std::endl;
            }
            else if (command.equals("PRINT")) {
                if (fileIsOpened()) print();
            }
            else if (command.equals("SELECT")) {
                std::cout << "Enter the name of the Id and key : ";

                String ID, Key;
                std::cin >> ID >> Key;
                if (fileIsOpened()) printAttribute(ID, Key);
            }
            else if (command.equals("SET")) {
                std::cout << "Enter the name of the ID key and value : ";

                String ID, Key, Value;
                std::cin >>ID>> Key >> Value;
                if (fileIsOpened()) setAttribute(ID, Key, Value);
            }
            else if (command.equals("ChildNodes")) {
                String ID;
                std::cout << "Enter the name of the ID : ";

                std::cin >> ID;
                if (fileIsOpened()) printChildren(ID);
            }
            else if (command.equals("CHILD")) {
                int pos;
                String ID;
                std::cout << "Enter the name of the ID and pos : ";

                std::cin >> ID;
                std::cin >> pos;
                if (fileIsOpened()) printChildByIndex(ID, pos);
            }
            else if (command.equals("TEXT")) {
                String ID;
                std::cout << "Enter the name of the ID : ";

                std::cin >> ID;
                if (fileIsOpened()) printText(ID);
            }
            else if (command.equals("DELETE")) {
                String ID, Key;
                std::cout << "Enter the name of the ID and key : ";

                std::cin >> ID >> Key;
                if (fileIsOpened()) removeAttribute(ID,Key);
            }
            else if (command.equals("NEWCHILD")) {
                std::cout << "Enter the name of the ID and type : ";

                String ID, Type;
                std::cin >> ID >> Type;
                if (fileIsOpened()) addChild(ID, Type);
            }
            else if (command.equals("XPATH")) {
                if (fileIsOpened()) xmlPath(parts[1]);
            }
            else {
                std::cout << "NO SUCH A COMMAND ! TRY AGAIN" << std::endl;
            }
        }
     
        
}
