#include <iostream>
#include <string>

#include "../universe.h"

static void help()
{
    std::cout
        << "create <name>\n"
        << "remove <name>\n"
        << "rename <old> <new>\n"
        << "change <name>\n"
        << "current\n"
        << "count\n"
        << "list\n"
        << "help\n"
        << "quit\n";
}

int main()
{
    universe u;
    help();
    std::string cmd;

    while (std::cin >> cmd)
    {
        if (cmd == "create") { std::string n; std::cin >> n; std::cout << (u.create(n) ? "ok" : "exists") << '\n'; }
        else if (cmd == "remove") { std::string n; std::cin >> n; std::cout << (u.remove(n) ? "ok" : "not_found") << '\n'; }
        else if (cmd == "rename") { std::string a, b; std::cin >> a >> b; std::cout << (u.rename(a, b) ? "ok" : "failed") << '\n'; }
        else if (cmd == "change") { std::string n; std::cin >> n; std::cout << (u.change(n) ? "ok" : "not_found") << '\n'; }
        else if (cmd == "current") { std::cout << (u.current() ? u.current()->name() : "none") << '\n'; }
        else if (cmd == "count") { std::cout << u.count() << '\n'; }
        else if (cmd == "list") { u.each([](world& w) { std::cout << w.name() << '\n'; }); std::cout << ".\n"; }
        else if (cmd == "help") { help(); std::cout << "ok\n"; }
        else if (cmd == "quit") { return 0; }
        else { std::cout << "unknown\n"; }
    }
}