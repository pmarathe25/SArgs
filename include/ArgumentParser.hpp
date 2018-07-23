#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>

namespace Stealth::Args {
    class ArgumentParser {
        public:
            // After parsing, store Args in a mapping of their full names -> contents.
            using StringMap = std::unordered_map<std::string, std::string>;

            ArgumentParser(std::string description = "");
            StringMap parse(int argc, const char* argv[]);
            StringMap& parse(int argc, const char* argv[], StringMap& args);
            void addPositionalArgument(std::string name, std::string description = "");
            void addArgument(const char* shortName, const char* name, const char* description, bool required = false);
            void addArgument(const char* name, const char* description, bool required = false);
            [[noreturn]] void exitPrint() const;

            const std::string& getExecutableName() const noexcept;
        private:
            // Hack to prevent compiler from converting const char* to bool, thereby causing calls to the wrong overload.
            template <typename... Args>
            void addArgument(Args&&... args);

            const std::string mDescription;
            std::string mExecName, mPositionalArgUsage, mArgUsage, mPositionalArgDescriptions, mArgDescriptions;
            std::unordered_set<std::string> mOptionalArgs, mRequiredArgs;
            StringMap mShortNames;
            std::vector<std::string> mPositionalArgs;
    };

} /* Stealth::Args */
