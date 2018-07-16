gs = 'git status'
gc = 'git commit'
go = 'git checkout'
hist = log --pretty=format:\"%h %ad | %s%d [%an]\" --graph --date=short
type = cat-file -t
dump = cat-file -p