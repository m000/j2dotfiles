-- helper functions -------------------------------------------------
local function path_exists(path)
  return (vim.uv or vim.loop).fs_stat(path)
end

-- bootstrap lazy.nvim, LazyVim and your plugins
require("config.lazy")

-- load nvimrc ------------------------------------------------------
local nvimrc = vim.fn.stdpath("config") .. "/nvimrc"
if path_exists(nvimrc) then
  vim.cmd(string.format("source %s", nvimrc))
end
