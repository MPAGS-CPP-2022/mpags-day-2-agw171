#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::string transformChar(const char inputChar){
    // Uppercase alphabetic characters
    std::string inputText;
    if (std::isalpha(inputChar)) {
        inputText += std::toupper(inputChar);
    }
    // Transliterate digits to English words
    switch (inputChar) {
        case '0':
            inputText += "ZERO";
            break;
        case '1':
            inputText += "ONE";
            break;
        case '2':
            inputText += "TWO";
            break;
        case '3':
            inputText += "THREE";
            break;
        case '4':
            inputText += "FOUR";
            break;
        case '5':
            inputText += "FIVE";
            break;
        case '6':
            inputText += "SIX";
            break;
        case '7':
            inputText += "SEVEN";
            break;
        case '8':
            inputText += "EIGHT";
            break;
        case '9':
            inputText += "NINE";
            break;
    }
    return inputText;
        // If the character isn't alphabetic or numeric, DONT do anything
}
bool processCommandLine(const std::vector<std::string>& args, bool& helpRequested, bool& versionRequested, std::string& inputFileName, std::string& outputFileName){
    if (helpRequested){
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        return 1;
    }
    if (versionRequested){
        std::cout<<"0.1.1"<<std::endl;
        return 1; 
    }
    if (!outputFileName.empty()) {
        std::cerr << "[warning] output to file ('" << outputFileName
                  << "') not implemented yet, using stdout\n";
    }
    if (!inputFileName.empty()) {
        std::cerr << "[warning] input from file ('" << inputFileName
                  << "') not implemented yet, using stdin\n";
    }
    return 0;
}
int main(int argc, char* argv[]){
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};
    const std::size_t nCmdLineArgs{cmdLineArgs.size()};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFileName{""};
    std::string outputFileName{""};

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
            helpRequested = true;
        } else if (cmdLineArgs[i] == "--version") {
            versionRequested = true;
        } else if (cmdLineArgs[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = cmdLineArgs[i + 1];
                ++i;
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << cmdLineArgs[i]
                      << "'\n";
            return 1;
        }
    }

    // processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFileName, outputFileName);
    if (processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFileName, outputFileName) == 1){
        return 0;
    }
    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // loop over each character from user input
    while (std::cin >> inputChar){
            inputText += {transformChar(inputChar)};
        }

    // Print out the transliterated text
    std::cout << inputText << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}