#include "ArgumentParser.hpp"
#include <iostream>

namespace Stealth::Args {
    ArgumentParser::ArgumentParser(std::string description) : mDescription(std::move(description)) { }

    ArgumentParser::StringMap ArgumentParser::parse(int argc, const char* argv[]) {
        ArgumentParser::StringMap args{};
        return parse(argc, argv, args);
    }

    ArgumentParser::StringMap& ArgumentParser::parse(int argc, const char* argv[], ArgumentParser::StringMap& args) {
        mExecName = std::string{argv[0]};
        // Check that there are enough arguments. Should be Executable + N positional + M (arg, value) pairs
        // DEBUG:
        std::cout << "Argc: " << argc << '\n';
        std::cout << "Minimum: " << (1 + mPositionalArgs.size() + mRequiredArgs.size() * 2) << '\n';

        if (argc < 1 + mPositionalArgs.size() + mRequiredArgs.size() * 2) exitPrint();

        int i{1};
        // First populate all the positional arguments.
        for (; i <= static_cast<int>(mPositionalArgs.size()); ++i) {

            // DEBUG:
            std::cout << "Found positional argument: " << argv[i] << '\n';

            args[mPositionalArgs[i - 1]] = argv[i];
        }
        // Then do the non positional ones.
        for (; i < argc; i += 2) {

            // DEBUG:
            std::cout << "Found flag: " << argv[i] << '\n';

            // If this is an unrecognized argument, exit.
            if (not mRequiredArgs.count(argv[i]) and not mOptionalArgs.count(argv[i]) and not mShortNames.count(argv[i])) exitPrint();
            // If this is a short name, get the long name.
            std::string arg{(argv[i][1] == '-') ? argv[i] : mShortNames[argv[i]]};
            // Remove leading dashes.
            args[arg.substr(2)] = argv[i + 1];
        }
        return args;
    }

    void ArgumentParser::addPositionalArgument(std::string name, std::string description) {
        // Add help.
        mArgUsage += " " + name;
        mArgDescriptions += name + '\t' + description + "\n";
        // Positional arguments are always required.
        mPositionalArgs.emplace_back(name);
        // DEBUG:
        std::cout << "Adding positional arg: " << name << '\n';
    }

    void ArgumentParser::addArgument(const char* shortName, const char* name, const char* description, bool required) {
        // Add help
        mArgUsage += (required ? " " : " [") + std::string{shortName} + " " + std::string{name}.substr(2) + (required ? "" : "]");
        mArgDescriptions += " " + std::string{shortName} + '\t' + std::string{name} + '\t' + description + '\n';
        // Add argument
        (required) ? mRequiredArgs.emplace(name) : mOptionalArgs.emplace(name);
        mShortNames.emplace(shortName, name);
    }

    void ArgumentParser::addArgument(const char* name, const char* description, bool required) {
        // Add help
        mArgUsage += (required ? " " : " [") + std::string{name} + " " + std::string{name}.substr(2) + (required ? "" : "]");
        mArgDescriptions += " " + '\t' + std::string{name} + '\t' + description + '\n';
        // Add argument
        (required) ? mRequiredArgs.emplace(name) : mOptionalArgs.emplace(name);
    }

    [[noreturn]] void ArgumentParser::exitPrint() const {
        std::cout << "Usage: " << mExecName << mArgUsage << '\n' << mArgDescriptions << std::endl;
        exit(1);
    }

    const std::string& ArgumentParser::getExecutableName() const noexcept {
        return mExecName;
    }

} /* Stealth::Args */
