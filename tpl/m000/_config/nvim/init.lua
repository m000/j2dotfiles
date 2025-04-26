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
})

