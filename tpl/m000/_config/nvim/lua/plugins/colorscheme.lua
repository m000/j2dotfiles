return {
    -- add themes
    { "craftzdog/solarized-osaka.nvim", lazy = true },
    { "dracula/vim", lazy = true },
    { "rose-pine/neovim", lazy = true, name = "rose-pine" },
    { "folke/tokyonight.nvim", lazy = true, priority = 1000, opts = {} },

    -- load preferred theme
    {
        "LazyVim/LazyVim",
        opts = {
            colorscheme = "solarized-osaka-storm",
        },
    },
}
