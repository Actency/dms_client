# Set path
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

# Get hostname
hostname=`hostname` 2> /dev/null

# Get distrib
if [ -f "/etc/system-release" ]; then
    distrib=`cat /etc/system-release`
else
    distrib=`python -c 'import platform; print platform.linux_distribution()[0] + " " + platform.linux_distribution()[1]'` 2> /dev/null
fi

# Get uptime
if [ -f "/proc/uptime" ]; then
    uptime=`cat /proc/uptime`
    uptime=${uptime%%.*}
    seconds=$(( uptime%60 ))
    minutes=$(( uptime/60%60 ))
    hours=$(( uptime/60/60%24 ))
    days=$(( uptime/60/60/24 ))
    uptime="$days"d", $hours"h", $minutes"m", $seconds"s""
else
    uptime=""
fi

# Get cpus number
if [ -f "/proc/cpuinfo" ]; then
    cpusnumber=`grep -c processor /proc/cpuinfo` 2> /dev/null
else
    cpusnumber=""
fi

# Get cpus usage
cpuusage=`top -bn1 | awk '/Cpu/ { cpu = 100 - $8 " %" }; END   { print cpu }'`

# Get load averages
loadavg=`uptime | awk -F'load average:' '{ print $2 }'` 2> /dev/null
# Remove leading whitespace from load averages
loadavg=`top -bn1 | grep load | awk '{printf "%.2f\n", $(NF-2)}'`

# Get disk usage
diskusage=`df -h / | awk '$NF=="/"{printf "%d / %d GB", $3,$2,$5}' | sed "s/^/\"/; s/$/\"/;"`
diskusage="["$diskusage"]"

# Get total memory
if [ -f "/proc/meminfo" ]; then
    totalram=`free -m | awk '/Mem/ {mem=$2};END {print mem}'`
    freeram=`free -m | awk '/buffers/ {mem=$4};END {print mem}'`
    usedram=`expr $totalram - $freeram`
    unit=MB
    memoryusage="$usedram / $totalram $unit"
else
    memoryusage=""
fi

# Get ip addresses using ip
if [ -n `command -v ip` ]; then
    ips=$(for i in `ip addr show | awk -F "/" '/inet .*\//{ gsub(/inet |^[ \t]+/, "", $1); if ($1 != "127.0.0.1") print $1 }' | sed "s/^/\"/; s/$/\"/;"`; do echo -n "${i}, "; done| sed 's/, $//');
    ips="["$ips"]"
# Try using ifconfig instead
else
    ips=`ifconfig | awk -F "[: ]+" '/inet addr:/ { if ($4 != "127.0.0.1") print $4 }'` 2> /dev/null
fi

# ips is empty, let's try and get ip addresses with python instead
if [ -z "${ips}" ]; then
    ips=`python -c 'import socket; print socket.gethostbyname(socket.gethostname())'` 2> /dev/null
fi

echo -n '{"hostname": "'$hostname'", "distrib": "'$distrib'", "uptime": "'$uptime'", "cpusnumber": '$cpusnumber', "cpuusage": "'$cpuusage'", "loadavg": "'$loadavg'", "memoryusage": "'$memoryusage'", "diskusage": '$diskusage', "ips": '$ips'}'
