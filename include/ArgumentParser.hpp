#pragma once
#include <Stealth/String>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

namespace Stealth::Args {
    class ArgumentParser {
        public:
            ArgumentParser(Stealth::String description = "");
            std::unordered_map<Stealth::String, Stealth::String> parse(int argc, const char* argv[]);
            std::string_view addPositionalArgument(Stealth::String name, Stealth::String description);

            std::string_view addArgument(Stealth::String shortName, Stealth::String name, Stealth::String description);
            std::string_view addArgument(Stealth::String name, Stealth::String description);

            std::string_view addRequiredArgument(Stealth::String shortName, Stealth::String name, Stealth::String description);
            std::string_view addRequiredArgument(Stealth::String name, Stealth::String description);

            [[noreturn]] void exitPrint() const;

            const Stealth::String& getExecutableName() const noexcept;
        private:
            Stealth::String mDescription, mExecName;
            // Maps arg -> desciption.
            std::vector<std::pair<Stealth::String, Stealth::String>> mPositionalArgs;
            std::unordered_set<std::string_view> mRequiredArgs;
            std::unordered_map<Stealth::String, Stealth::String> mArgs;
            std::unordered_map<Stealth::String, std::string_view> mShortNames;
    };

} /* Stealth::Args */
