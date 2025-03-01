-- helper functions -------------------------------------------------
function path_exists(path) return (vim.uv or vim.loop).fs_stat(path) end

-- load nvimrc ------------------------------------------------------
local nvimrc = vim.fn.stdpath("config") .. "/nvimrc"
if path_exists(nvimrc) then vim.cmd(string.format("source %s", nvimrc)) end

-- bootstrap lazy.nvim ----------------------------------------------
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not path_exists(lazypath) then
    vim.fn.system({
        "git",
        "clone",
        "--filter=blob:none",
        "https://github.com/folke/lazy.nvim.git",
        "--branch=stable", -- latest stable release
        lazypath,
    })
end
vim.opt.rtp:prepend(lazypath)

-- lazy.nvim plugins ------------------------------------------------
require("lazy").setup({
    { import = "plugins" },
	"airblade/vim-gitgutter",
	"neovim/nvim-lspconfig",
})

local lspconfig = require('lspconfig')
lspconfig.pylsp.setup{}

-- lazy.nvim plugins ------------------------------------------------
local prev_mouse_mode = ''
vim.api.nvim_set_keymap('n', '<M-m>', ':lua ToggleMouse()<CR>', { noremap = true, silent = true })

-- Function to toggle mouse mode
function ToggleMouse()
    -- Check if the previous mouse mode is stored
    if prev_mouse_mode == '' then
        -- If not stored, store the current mouse mode
        prev_mouse_mode = vim.o.mouse
    end

    -- Toggle between disabling the mouse and the previous mouse mode
    if vim.o.mouse == '' then
        vim.o.mouse = prev_mouse_mode
        print("Mouse enabled")
    else
        prev_mouse_mode = vim.o.mouse
        vim.o.mouse = ''
        print("Mouse disabled")
    end
end

