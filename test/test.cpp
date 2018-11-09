#include "interfaces/SArgs"
#include <iostream>

int main(int argc, char const *argv[]) {
    Stealth::Args::ArgumentParser parser{"Test executable"};
    // Add some arguments.
    parser.addArgument("-a", "--arg0", "Some argument");
    parser.addArgument("--arg1", "Some other argument");

    // Add some positional arguments.
    parser.addPositionalArgument("message", "The message to show");

    // Parse!
    const auto args = parser.parse(argc, argv);
    // Display all found args.
    std::cout << "Executable: " << parser.getExecutableName() << " invoked with arguments: "<< '\n';
    for (auto [name, value] : args) {
        std::cout << '\t' << name << ": " << value << '\n';
    }
    std::cout << std::endl;
}
