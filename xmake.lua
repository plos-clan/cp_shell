set_project("CPShell")
add_rules("mode.debug", "mode.release")
set_languages("clatest")
set_warnings("all", "extra")
add_requires("pl_readline main")

target("cplibc")
    set_kind("static")
    set_toolchains("clang")

    local base_dir = "submod/cplibc"
    add_files("cplibc/src/**.c")
    add_includedirs("cplibc/include", {public = true})
    add_includedirs("cplibc/include/types", {public = true})
    add_cflags("-nostdlib", "-fno-stack-protector")

target("shell")
    set_kind("binary")
    add_deps("cplibc")
    add_packages("pl_readline")
    set_toolchains("clang")

    add_files("src/**.c")
    add_includedirs("include")

    add_cflags("-nostdlib", "-fno-stack-protector")
    add_ldflags("-nostdlib", "-Wl,--whole-archive")

    before_build(function (target)
        local hash = try { function()
            local result = os.iorun("git rev-parse --short HEAD")
            return result and result:trim()
        end }
        if hash then target:add("defines", "GIT_VERSION=\""..hash.."\"") end
    end)

package("pl_readline")
    set_urls("https://github.com/plos-clan/pl_readline.git")

    on_install(function (package)
        io.writefile("xmake.lua", [[
            add_rules("mode.release", "mode.debug")
            target("pl_readline")
                set_kind("static")
                set_toolchains("clang")

                add_files("src/*.c")
                add_includedirs("include", {public = true})

                add_defines("PL_ENABLE_HISTORY_FILE=0")
                add_cflags("-mno-80387", "-mno-mmx", "-DNDEBUG")
                add_cflags("-mno-sse", "-mno-sse2", "-mno-red-zone")
                add_cflags("-nostdlib", "-fno-builtin", "-fno-stack-protector")
            ]])
        import("package.tools.xmake").install(package)
        os.cp("include/*.h", package:installdir("include"))
    end)
package_end()
