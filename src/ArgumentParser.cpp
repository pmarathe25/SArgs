#include "ArgumentParser.hpp"
#include <iostream>
#include <algorithm>

namespace Stealth::Args {

    namespace {
        std::string& toUpper(std::string&& str) {
            for (auto& c: str) c = toupper(c);
            return str;
        }
    }

    ArgumentParser::ArgumentParser(std::string description) : mDescription(std::move(description)) { }

    ArgumentParser::StringMap ArgumentParser::parse(int argc, const char* argv[]) {
        ArgumentParser::StringMap args{};
        return parse(argc, argv, args);
    }

    ArgumentParser::StringMap& ArgumentParser::parse(int argc, const char* argv[], ArgumentParser::StringMap& args) {
        mExecName = std::string{argv[0]};
        // Check that there are enough arguments. Should be Executable + N positional + M (arg, value) pairs
        if (static_cast<size_t>(argc) < 1 + mPositionalArgs.size() + mRequiredArgs.size() * 2) exitPrint();

        int i{1};
        // First populate all the positional arguments.
        for (; i <= static_cast<int>(mPositionalArgs.size()); ++i) args[mPositionalArgs[i - 1]] = argv[i];
        // Then do the non positional ones.
        for (; i < argc; i += 2) {
            // If this is an unrecognized argument, exit.
            if (not mRequiredArgs.count(argv[i]) and not mOptionalArgs.count(argv[i]) and not mShortNames.count(argv[i])) exitPrint();
            // If this is a short name, get the long name.
            std::string arg{(argv[i][1] == '-') ? argv[i] : mShortNames[argv[i]]};
            // If this is a required argument, mark it as having been seen.
            if (mRequiredArgs.count(arg)) mRequiredArgs[arg] = true;
            // Remove leading dashes.
            args[arg.substr(2)] = argv[i + 1];
        }
        // If all required args are not found, do exitPrint.
        bool requiredArgsFound = true;
        for (auto [name, seen] : mRequiredArgs) {
            requiredArgsFound &= seen;
            if (not seen) std::cout << "[ERROR] Missing required argument: " << name << std::endl;
        }
        if (not requiredArgsFound) exitPrint();
        return args;
    }

    void ArgumentParser::addPositionalArgument(std::string name, std::string description) {
        // Add help.
        mPositionalArgUsage += " " + name;
        mPositionalArgDescriptions += '\t' + name + '\t' + description + "\n";
        // Positional arguments are always required.
        mPositionalArgs.emplace_back(name);
    }

    void ArgumentParser::addArgument(const char* shortName, const char* name, const char* description, bool required) {
        std::string strShortName{shortName}, strName{name}, strDescription{description};
        // Add help
        mArgUsage += (required ? " " : " [") + strShortName + " " + toUpper(strName.substr(2)) + (required ? "" : "]");
        mArgDescriptions += "  " + strShortName + '\t' + strName + '\t' + strDescription + '\n';
        // Add argument
        if (required) mRequiredArgs.emplace(strName, false); else mOptionalArgs.emplace(strName);
        mShortNames.emplace(strShortName, strName);
    }

    void ArgumentParser::addArgument(const char* name, const char* description, bool required) {
        std::string strName{name}, strDescription{description};
        // Add help
        mArgUsage += (required ? " " : " [") + strName + " " + toUpper(strName.substr(2)) + (required ? "" : "]");
        mArgDescriptions += "  \t" + strName + '\t' + strDescription + '\n';
        // Add argument
        if (required) mRequiredArgs.emplace(strName, false); else mOptionalArgs.emplace(strName);
    }

    [[noreturn]] void ArgumentParser::exitPrint() const {
        std::cout << "Usage: " << mExecName << mPositionalArgUsage << mArgUsage
            << "\nPositional Arguments:\n" << mPositionalArgDescriptions << "\nFlags:\n" << mArgDescriptions << std::endl;
        exit(1);
    }

    const std::string& ArgumentParser::getExecutableName() const noexcept {
        return mExecName;
    }

} /* Stealth::Args */
