`ls`: list, Windows equi `dir`
`ls -l`: `r` - read, `w` - write, `x` - executable, `d` - dir, `l` - link
`ls -la`: display all
`ls -la | grep sda`: `|` to combine commands, `grep sda` filter and only keep those with `sda` in name

`pwd`: present working directory

`cd`: change directory
`cd /`: to root dir
`cd ~/`: to home dir
`cd ..`: back to outer dir

`cd dev`: to *devices* dir, listing all devices available

`rm`: remove
`rmdir`: remove dir

`wheel`: user group, almost as powerful as root

`mkdir`: make dir

`history`: list out all commands executed
`!(commandNumber)`: run the commands of that number listed in `history` results
`.bash_history`: file storing commands for `history`

## To access usb (applicable to other file systems)
Plug in, mkdir in `mnt` (mount) folder `mkdir usb`
Mount to that dir `mount /dev/sda /mnt/usb`
------------

## To remove usb (applicable to other file systems)
Unmount the device `umount /dev/sda3`
Unplug
------------

`whoami`: show current user
`exit`: log out of the user
If being `root` user, don't need `sudo`. But using `root` user is not recommended.
`su`: change user to `root`

`Ctrl + Alt + F#`: open new terminal
`tty#`: current terminal

## Access to pins of Pi
`/usr/linux`: contains header files associated with hardware
`/usr/include`: contains header files for `user`
`/sys/`: access to hardware and application functions

`echo "21" > /sys/class/gpio/export`: access GPIO 21, `>` to redirect to defined dir
`echo "out" > /sys/class/gpio/gpio21/direction`: set direction of GPIO 21 to be an output
`echo "1" > /sys/class/gpio/gpio21/value`: set GPIO 21 output logic 1

`echo "21" > /sys/class/gpio/unexport`: unlink/destroy GPIO 21 from system
------------