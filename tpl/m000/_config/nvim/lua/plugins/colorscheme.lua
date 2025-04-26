return {
  -- add themes
  { "craftzdog/solarized-osaka.nvim", name = "solarized-osaka", lazy = true },
  { "dracula/vim", name = "dracula", lazy = true },
  { "rose-pine/neovim", name = "rose-pine", lazy = true },
  { "folke/tokyonight.nvim", name = "tokyonight", lazy = true, priority = 1000, opts = {} },

  -- load preferred theme
  {
    "LazyVim/LazyVim",
    opts = {
      colorscheme = "solarized-osaka",
    },
  },
}
