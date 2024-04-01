return {
    {
        "nvim-treesitter/nvim-treesitter",
        build = ":TSUpdate",
        config = function()
            local configs = require("nvim-treesitter.configs")
            configs.setup({
                ensure_installed = {
                    "bash",
                    "c",
                    "cpp",
                    "css",
                    "dockerfile",
                    "groovy",
                    "html",
                    "javascript",
                    "json",
                    "lua",
                    "make",
                    "markdown",
                    "python",
                    "query",
                    "regex",
                    "rust",
                    "typescript",
                    "vim",
                    "vimdoc",
                    "yaml",
                },
                sync_install = false,
                highlight = { enable = true },
                indent = { enable = true },
            })
        end,
    },
}
