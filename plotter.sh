#!/bin/sh
#get current process number...we will need it later to track down children processes
curpid="$$"
#send file name (full extension) to and start the c program
echo -n "Enter a name for the data file (no extension) > "
read input
extension=".txt"
input=$input$extension
base=${PWD}
subdir="data"
new_path=$base/$subdir/$input
echo $new_path | ./mhsPlotter &

#get window size, must be integer
num=true
while $num
do
  echo -n "Set window size in seconds (enter an integer) > "
  read window
    if [ $window -eq $window 2>/dev/null ]
    then
         num=false
    else
        echo "$window bad entry, please enter window size in integer seconds"
    fi
done

#kill whole process tree on exit...including background script getting data from mhs
finish(){
  echo "finished..."
  
  #get children, gonna killem
  cpid=`pgrep -P $curpid`  #&& echo "$(basename $0) pid: $curpid; child pids:" $cpid
#kill the child pids and main pid
kill $cpid
kill $curpid
#sleep 0.5
#check on children
#for i in $cpid; do
#  echo -n "PID: $i; Orig PPID: $curpid; Cur PPID: "`/usr/bin/ps --ppid $i | grep -Eo '[0-9]{3,}'`
#done
}
#set trap for when ctrl c pressed, signal SIGINT is sent, which happens to be "2" below...wtf
trap finish 2

export FOO=$window
export name=$new_path
./refresher.sh &

echo "Press ctrl_c to exit!" 

while :
do
  sleep 1
done
