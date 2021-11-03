" see vim options at :options , also :viusage, :help, :set all
set nocompatible

" vimscript stuff learnvimscriptthehardway.stevelosh.com/

" activate line numbering
set nu

let skip_defaults_vim=1

" show columns/row ruler on the colon command line 
set ruler

set foldmethod=manual
set nofoldenable
"
set textwidth=78

" show visual/ex mode tag
set showmode
set autowrite
" --------------- TAB SETTINGS ------------------
" Sets << , >> operation tab spacing
set shiftwidth=2
set tabstop=2
set softtabstop=2
set expandtab

" Allows you to backspace at whatever your tabstop is
set smarttab
set autoindent
set smartindent
" Turns off a metric **** ton of things so that pasting works correctly
"
"set paste
filetype plugin indent on
"---------------- Color & Highlight Settings------------------------
color desert

"Run this function to find out what your cursor is currently
"highlightning so that you can change it.
function! <SID>SynStack()
  if !exists("*synstack")
    return
  endif
    echo map(synstack(line('.'), col('.')), 'synIDattr(v:val, "name")')
endfunc
"__________________________________________________________________
"Start at the last place you were editing
au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif

" Function Example
" echom gives you the call + return value, where echo just gives the msg no return
fu! Greet()
  echo "Hello World!"
endf

" Command Example - Calls Greet
command! Greet call Greet()

" To see all Vim console messages, do the command: 

" Vim Command Examples:
" :r!date
" outputs: Tue Nov  2 22:31:43 UTC 2021
"_____________________________ Function Mappings  ________________
map <F1> :call <SID>SynStack()<CR>

"------------------------------- Auto Commands  -------------------
"example:
au FileType markdown,pandoc hi Title ctermfg=yellow ctermbg=NONE
au FileType markdown,pandoc hi Operator ctermfg=yellow ctermbg=NONE 
"------------------------------------------------------------------

