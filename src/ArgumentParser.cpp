#include "ArgumentParser.hpp"
#include <iostream>
#include <algorithm>

namespace Stealth::Args {
    ArgumentParser::ArgumentParser(Stealth::String description) : mDescription(std::move(description)) { }

    std::unordered_map<Stealth::String, Stealth::String> ArgumentParser::parse(int argc, const char* argv[]) {
        mExecName = Stealth::String{argv[0]};

        std::unordered_map<Stealth::String, Stealth::String> arguments{};
        int positionalIndex = 0;
        int requiredArgsFound = 0;
        // Parse!
        for (int i = 1; i < argc; ++i) {
            Stealth::String arg{argv[i]};
            if (arg.startsWith("--") or arg.startsWith("-")) {
                // Find the value of the argument. Supports both `--arg=value` and `--arg value` syntax.
                Stealth::String value{};
                size_t equalPos = arg.find("=");
                if (equalPos != Stealth::String::npos) {
                    value = arg.substr(equalPos);
                } else {
                    if (i + 1 >= argc) exitPrint();
                    value = argv[++i];
                }
                // Add it to the map. Expand if it's a short name. Disallow duplicates.
                arg = mShortNames.count(arg) ? mShortNames[arg] : arg;
                if (mArgs.count(arg) and not arguments.count(arg)) {
                    arguments[arg] = value;
                    requiredArgsFound += mRequiredArgs.count(arg);
                } else {
                    exitPrint();
                }
            } else {
                arguments[mPositionalArgs[positionalIndex++].first] = arg;
            }
        }
        // Validate.
        if (requiredArgsFound != mRequiredArgs.size() or positionalIndex != mPositionalArgs.size()) {
            exitPrint();
        }
        return arguments;
    }

    std::string_view ArgumentParser::addPositionalArgument(Stealth::String name, Stealth::String description) {
        // Positional arguments are always required.
        return mPositionalArgs.emplace_back(name, description).first;
    }

    std::string_view ArgumentParser::addArgument(Stealth::String shortName, Stealth::String name, Stealth::String description) {
        std::string_view nameView = addArgument(name, description);
        mShortNames[shortName] = nameView;
        return nameView;
    }

    std::string_view ArgumentParser::addArgument(Stealth::String name, Stealth::String description) {
        auto [inserted, success] = mArgs.insert(std::make_pair(name, description));
        return inserted->first;
    }

    std::string_view ArgumentParser::addRequiredArgument(Stealth::String shortName, Stealth::String name, Stealth::String description) {
        std::string_view nameView = addRequiredArgument(name, description);
        mShortNames[shortName] = nameView;
        mRequiredArgs.insert(nameView);
        return nameView;
    }

    std::string_view ArgumentParser::addRequiredArgument(Stealth::String name, Stealth::String description) {
        auto [inserted, success] = mArgs.insert(std::make_pair(name, description));
        mRequiredArgs.insert(inserted->first);
        return inserted->first;
    }

    [[noreturn]] void ArgumentParser::exitPrint() const {
        Stealth::String positionalDescrs, requiredDescrs, optionalDescrs;
        std::cout << mDescription << '\n'
            << "Usage: " << mExecName;
        for (const auto& [positional, descr] : mPositionalArgs) {
            std::cout << " " << positional;
            positionalDescrs += "\t" + positional + ": " + descr + "\n";
        }
        // Create an inverse mapping of required arg names to their short names.
        std::unordered_map<std::string_view, Stealth::String> shortNames;
        for (const auto& [shortName, full] : mShortNames) {
            shortNames[full] = shortName;
        }

        for (const auto& [name, descr] : mArgs) {
            if (mRequiredArgs.count(name)) {
                std::cout << " [" << name << " " << name.toUpper().removePrefix("--") << "]";
                requiredDescrs += "\t" + (shortNames.count(name) ? shortNames[name] : "") + "\t" + name + ": " + descr + "\n";
            } else {
                std::cout << " " << name << " " << name.toUpper().removePrefix("--");
                optionalDescrs += "\t" + (shortNames.count(name) ? shortNames[name] : "") + "\t" + name + ": " + descr + "\n";
            }
        }
        std::cout << "\n"
            << (positionalDescrs.size() ? "\nPositional Args:\n" + positionalDescrs : "")
            << (requiredDescrs.size() ? "\nRequired Args:\n" + requiredDescrs : "")
            << (optionalDescrs.size() ? "\nOptional Args:\n" + optionalDescrs : "")
            << std::flush;
        exit(1);
    }

    const Stealth::String& ArgumentParser::getExecutableName() const noexcept {
        return mExecName;
    }

} /* Stealth::Args */
