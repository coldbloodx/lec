#/bin/bash

function create_user()
{
    vnc_pids=`pgrep Xvnc4`
    echo $vnc_pids
    if [ ! -z "$vnc_pids" ]; then
        echo -e "warning vnc is alive, pids:\n$vnc_pids\nkill them all..."
        kill -9 `pgrep Xvnc4`
        sleep 5
    fi
    prefix='pub'

    if [ ! -z $1 ]; then
        prefix=$1
        echo "create user with specified prefix"
    fi

    for((i=1;i<9;i++)) do
        username=$prefix$i
        echo "trying del existing user $prefix$i"
        deluser $username
        echo "creating user $username..."
        #echo "adduser $prefix$i --home /home/$prefix$i --shell /bin/bash --ingroup users --disabled-password --quiet --disabled-password --gecos"
        adduser $username --home /home/$username --shell /bin/bash --ingroup users --quiet --disabled-password --gecos $prefix$i > /dev/null 2>&1
        #echo "passwd --stdin $prefix$i"
        echo "create user password for user: $username..."
        echo -e "$username@123\n$username@123" |passwd "$username" > /dev/null 2>&1
        echo "create vnc password for user: $username..."
        vnc_pass_dir="/home/$username/.vnc"
        vnc_pass_file="$vnc_pass_dir/passwd"
        [ ! -d $vnc_pass_file ] && mkdir -p $vnc_pass_dir
        echo -e "$username@123\n$username@123" |vnc4passwd "$vnc_pass_file" > /dev/null 2>&1
        chown -R $prefix$i:users $vnc_pass_dir
        vnc_start_file="/home/$username/.vnc/xstartup"
        cat > $vnc_start_file << TAG
#!/bin/sh

# Uncomment the following two lines for normal desktop:
# unset SESSION_MANAGER
# exec /etc/X11/xinit/xinitrc

[ -x /etc/vnc/xstartup ] && exec /etc/vnc/xstartup
[ -r \$HOME/.Xresources ] && xrdb \$HOME/.Xresources
xsetroot -solid grey
vncconfig -iconic &
#x-terminal-emulator -geometry 80x24+10+10 -ls -title "\$VNCDESKTOP Desktop" &
#x-window-manager &
x-term -geometry 1024x768  -ls -title "\$VNCDESKTOP Desktop" &
gnome-session&
TAG
       chown $username:users /home/$username/.vnc/xstartup
       chmod 755 /home/$username/.vnc/xstartup
    done
}

function create_vncservice()
{
    service_file=/etc/init.d/vncservers
    echo "create vnc service script"
    cat > $service_file << TAG 
#!/usr/bin/env bash

vnc=\`which vnc4server\`

function start()
{
    username_prefix=pub
    for((i=1;i<9;i++))
    do
        username=\$username_prefix\$i
        rm -f /home/\$username/.vnc/{*.pid,*.log}
        rm -f "/tmp/.X11-unix/X\$i"
        rm -f "/tmp/.X\$i-lock"
        sleep 1
        su \$username -c vnc4server :\$i
    done
}

case "\$1" in
    start)
        start
        ;;
    stop)
        pkill -9 Xvnc4
        ;;
    status)
        vpn_pid=\`pgrep Xvnc4\`
        if [ -z "\$vpn_pid" ]; then
            echo "vpn service is not start"
        else
            echo -e "vpn is running, pids:\n\$vpn_pid"
        fi
        ;;
    restart)
        pkill -9 Xvnc4
        sleep 3
        start
        ;;
    *)
        echo "Usage: vncserver(start|stop|status|restart)"
        exit 1
        ;;
esac
TAG
    chmod 755 $service_file
    vnc_service=vncservers
    echo "create vnc service..."
    update-rc.d -f $vnc_service remove
    update-rc.d $vnc_service start 99 2 3 4 5 . stop 0 1 6 . 
    echo "start vnc servers, please wait..."
    /etc/init.d/$vnc_service start > /dev/null 2>&1
    echo -e "all things done, vnc servers:"
    /etc/init.d/$vnc_service status
    echo -e "please run:"
    echo -e "for vnc service start, please run:service $vnc_service start "
    echo -e "for vnc service stop, please run:service $vnc_service stop "
    echo -e "for vnc service status, please run:service $vnc_service status "
}

function install_vnc
{
    vnc_installed=`which vnc4server`
    if [ $? ]; then
        echo "vnc server not installed, installing vncserver"
        apt-get install vnc4server -y > /dev/null 2>&1
        sleep 3
    fi
}

#main
install_vnc
create_user
create_vncservice
