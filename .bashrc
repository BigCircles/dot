case $- in
*i*) ;; 
*) return ;;
esac
# man bash - search for PROMPTING for prompt options and cmd sequences.
# Environment Variables


export TERM=xterm-256color
# Exports added by @stremler
export GIT_USERNAME="BigCircles"
export PATH='$PATH:~/repos/dot/scripts'
export DOTPATH="/home/stremler/repos/dot"
export WEATHER_API="b7eabd4f923c3357d060db217e7c6f39"
export ZETPATH="/home/stremler/repos/zet"
export CDPATH=$CDPATH:"/home/stremler/bookmarks"
export LABDIR="/home/stremler/repos/labs"
#------------- -Prompt --------------------------

export PS1='\[\e[0;94m\]\u\[\e[0;2m\]@\[\e[0;91m\]\h:\[\e[0;33m\]\W\$\[\e[0m\] '

#-----------------------------------------------
export EDITOR=vi
export VISUAL=vi
export PAGER="less"
export MANPAGER='less -I -X'


 #-------------- Path  --------------------------

  export PATH="$HOME/.local/bin:$PATH"

  #pathappend
pathappend(){
  declare arg
  for arg in "$@"; do
    test -d "${arg}" || continue
    PATH=${PATH//:${arg}:/:} 
    PATH=${PATH/#${arg}:/}
    PATH=${PATH/%:${arg}/}
    export PATH="${PATH:+"${PATH}:"}${arg}"
done
}
  #pathprepend
pathprepend(){
  declare arg
  for arg in "$@"; do
    test -d "${arg}" || continue
    PATH=${PATH//:${arg}:/:} # if exists delete it
    PATH=${PATH/#${arg}:/}
    PATH=${PATH/%:${arg}/}
    export PATH="${arg}${PATH:+":${PATH}"}"
done
}

export SCRIPTS=~/repos/dot/scripts
mkdir -p "$SCRIPTS" &>/dev/null

#remember first arg will be first in the path
pathprepend \
  ~/.local/bin \
  $SCRIPTS \
  ~/repos/education/headfirstc/exercises


#remember last arg will be the first in the path
pathappend \
  /usr/local/bin \
  /usr/local/sbin \
  /usr/games \
  /usr/sbin \
  /usr/bin \
  /snap/bin \
  /sbin \

 #-------------- CDPATH ------------------------

export CDPATH=.:\
~:\
~/.local:\
~/.local/bin:\
~/.local/bin/scripts:\
~/repos:\
~/repos/scripts:\
~/repos/labs:\
/home/stremler/repos/education/headfirstc/exercises:\
/home/stremler/repos/education/headfirstc:\



# example path ~/repos/zet:\

 #------------- Pager Stuff ---------------------

if test -x /usr/bin/lesspipe; then
        export LESSOPEN="| /usr/bin/lesspipe %s";
        export LESSCLOSE="/usr/bin/lesspipe %s %s";
fi

export LESS_TERMCAP_mb="[0;35m" #magenta
export LESS_TERMCAP_md="[33m" #yellow
export LESS_TERMCAP_me=""
export LESS_TERMCAP_se=""
export LESS_TERMCAP_so="[34m" #blue
export LESS_TERMCAP_us="[4m" #underline
export LESS_TERMCAP_ue=""
#-------------- dir colors ---------------------

if command -v "dircolors" &>/dev/null; then
  if test -r ~/.dircolors; then
    eval "$(dircolors -b ~/.dircolors)"
  else
    eval "$(dircolors -b)"
  fi
fi

alias ls='ls -h --color=auto'


# ------------- Bash Shell Options --------------
shopt -s checkwinsize
shopt -s globstar

# ------------- History -------------------------

export HISTCONTROL=ignoreboth
export HISTSIZE=5000
export HISTFILESIZE=10000

set -o vi
shopt -s histappend

# ------------- Alias' --------------------------

# Alias added by @Stremler
alias c='clear'
alias labs='cd $LABDIR'
alias scripts='cd $SCRIPTS'
alias dot='cd $DOTPATH'
alias ?='duck'
alias ??='google'
alias ???='bing'

#----------------- Bash Completion --------------

# enable bash completion in interactive shells
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

complete -C completiontest completiontest
complete -C weather weather
complete -C lab lab
complete -C ctitle ctitle
complete -C colors colors
