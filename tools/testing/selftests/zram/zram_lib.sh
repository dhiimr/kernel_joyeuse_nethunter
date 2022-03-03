#!/bin/sh
# Copyright (c) 2015 Oracle and/or its affiliates. All Rights Reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it would be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.
#
# Author: Alexey Kodanev <alexey.kodanev@oracle.com>
# Modified: Naresh Kamboju <naresh.kamboju@linaro.org>

<<<<<<< HEAD
MODULE=0
dev_makeswap=-1
dev_mounted=-1

# Kselftest framework requirement - SKIP code is 4.
ksft_skip=4
=======
dev_makeswap=-1
dev_mounted=-1
dev_start=0
dev_end=-1
module_load=-1
sys_control=-1
# Kselftest framework requirement - SKIP code is 4.
ksft_skip=4
kernel_version=`uname -r | cut -d'.' -f1,2`
kernel_major=${kernel_version%.*}
kernel_minor=${kernel_version#*.}
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

trap INT

check_prereqs()
{
	local msg="skip all tests:"
	local uid=$(id -u)

	if [ $uid -ne 0 ]; then
		echo $msg must be run as root >&2
		exit $ksft_skip
	fi
}

<<<<<<< HEAD
=======
kernel_gte()
{
	major=${1%.*}
	minor=${1#*.}

	if [ $kernel_major -gt $major ]; then
		return 0
	elif [[ $kernel_major -eq $major && $kernel_minor -ge $minor ]]; then
		return 0
	fi

	return 1
}

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
zram_cleanup()
{
	echo "zram cleanup"
	local i=
<<<<<<< HEAD
	for i in $(seq 0 $dev_makeswap); do
		swapoff /dev/zram$i
	done

	for i in $(seq 0 $dev_mounted); do
		umount /dev/zram$i
	done

	for i in $(seq 0 $(($dev_num - 1))); do
=======
	for i in $(seq $dev_start $dev_makeswap); do
		swapoff /dev/zram$i
	done

	for i in $(seq $dev_start $dev_mounted); do
		umount /dev/zram$i
	done

	for i in $(seq $dev_start $dev_end); do
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		echo 1 > /sys/block/zram${i}/reset
		rm -rf zram$i
	done

<<<<<<< HEAD
}

zram_unload()
{
	if [ $MODULE -ne 0 ] ; then
		echo "zram rmmod zram"
=======
	if [ $sys_control -eq 1 ]; then
		for i in $(seq $dev_start $dev_end); do
			echo $i > /sys/class/zram-control/hot_remove
		done
	fi

	if [ $module_load -eq 1 ]; then
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		rmmod zram > /dev/null 2>&1
	fi
}

zram_load()
{
<<<<<<< HEAD
	# check zram module exists
	MODULE_PATH=/lib/modules/`uname -r`/kernel/drivers/block/zram/zram.ko
	if [ -f $MODULE_PATH ]; then
		MODULE=1
		echo "create '$dev_num' zram device(s)"
		modprobe zram num_devices=$dev_num
		if [ $? -ne 0 ]; then
			echo "failed to insert zram module"
			exit 1
		fi

		dev_num_created=$(ls /dev/zram* | wc -w)

		if [ "$dev_num_created" -ne "$dev_num" ]; then
			echo "unexpected num of devices: $dev_num_created"
			ERR_CODE=-1
		else
			echo "zram load module successful"
		fi
	elif [ -b /dev/zram0 ]; then
		echo "/dev/zram0 device file found: OK"
	else
		echo "ERROR: No zram.ko module or no /dev/zram0 device found"
		echo "$TCID : CONFIG_ZRAM is not set"
		exit 1
	fi
=======
	echo "create '$dev_num' zram device(s)"

	# zram module loaded, new kernel
	if [ -d "/sys/class/zram-control" ]; then
		echo "zram modules already loaded, kernel supports" \
			"zram-control interface"
		dev_start=$(ls /dev/zram* | wc -w)
		dev_end=$(($dev_start + $dev_num - 1))
		sys_control=1

		for i in $(seq $dev_start $dev_end); do
			cat /sys/class/zram-control/hot_add > /dev/null
		done

		echo "all zram devices (/dev/zram$dev_start~$dev_end" \
			"successfully created"
		return 0
	fi

	# detect old kernel or built-in
	modprobe zram num_devices=$dev_num
	if [ ! -d "/sys/class/zram-control" ]; then
		if grep -q '^zram' /proc/modules; then
			rmmod zram > /dev/null 2>&1
			if [ $? -ne 0 ]; then
				echo "zram module is being used on old kernel" \
					"without zram-control interface"
				exit $ksft_skip
			fi
		else
			echo "test needs CONFIG_ZRAM=m on old kernel without" \
				"zram-control interface"
			exit $ksft_skip
		fi
		modprobe zram num_devices=$dev_num
	fi

	module_load=1
	dev_end=$(($dev_num - 1))
	echo "all zram devices (/dev/zram0~$dev_end) successfully created"
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

zram_max_streams()
{
	echo "set max_comp_streams to zram device(s)"

<<<<<<< HEAD
	local i=0
=======
	kernel_gte 4.7
	if [ $? -eq 0 ]; then
		echo "The device attribute max_comp_streams was"\
		               "deprecated in 4.7"
		return 0
	fi

	local i=$dev_start
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	for max_s in $zram_max_streams; do
		local sys_path="/sys/block/zram${i}/max_comp_streams"
		echo $max_s > $sys_path || \
			echo "FAIL failed to set '$max_s' to $sys_path"
		sleep 1
		local max_streams=$(cat $sys_path)

		[ "$max_s" -ne "$max_streams" ] && \
			echo "FAIL can't set max_streams '$max_s', get $max_stream"

		i=$(($i + 1))
<<<<<<< HEAD
		echo "$sys_path = '$max_streams' ($i/$dev_num)"
=======
		echo "$sys_path = '$max_streams'"
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	done

	echo "zram max streams: OK"
}

zram_compress_alg()
{
	echo "test that we can set compression algorithm"

<<<<<<< HEAD
	local algs=$(cat /sys/block/zram0/comp_algorithm)
	echo "supported algs: $algs"
	local i=0
=======
	local i=$dev_start
	local algs=$(cat /sys/block/zram${i}/comp_algorithm)
	echo "supported algs: $algs"

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	for alg in $zram_algs; do
		local sys_path="/sys/block/zram${i}/comp_algorithm"
		echo "$alg" >	$sys_path || \
			echo "FAIL can't set '$alg' to $sys_path"
		i=$(($i + 1))
<<<<<<< HEAD
		echo "$sys_path = '$alg' ($i/$dev_num)"
=======
		echo "$sys_path = '$alg'"
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	done

	echo "zram set compression algorithm: OK"
}

zram_set_disksizes()
{
	echo "set disk size to zram device(s)"
<<<<<<< HEAD
	local i=0
=======
	local i=$dev_start
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	for ds in $zram_sizes; do
		local sys_path="/sys/block/zram${i}/disksize"
		echo "$ds" >	$sys_path || \
			echo "FAIL can't set '$ds' to $sys_path"

		i=$(($i + 1))
<<<<<<< HEAD
		echo "$sys_path = '$ds' ($i/$dev_num)"
=======
		echo "$sys_path = '$ds'"
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	done

	echo "zram set disksizes: OK"
}

zram_set_memlimit()
{
	echo "set memory limit to zram device(s)"

<<<<<<< HEAD
	local i=0
=======
	local i=$dev_start
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	for ds in $zram_mem_limits; do
		local sys_path="/sys/block/zram${i}/mem_limit"
		echo "$ds" >	$sys_path || \
			echo "FAIL can't set '$ds' to $sys_path"

		i=$(($i + 1))
<<<<<<< HEAD
		echo "$sys_path = '$ds' ($i/$dev_num)"
=======
		echo "$sys_path = '$ds'"
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	done

	echo "zram set memory limit: OK"
}

zram_makeswap()
{
	echo "make swap with zram device(s)"
<<<<<<< HEAD
	local i=0
	for i in $(seq 0 $(($dev_num - 1))); do
=======
	local i=$dev_start
	for i in $(seq $dev_start $dev_end); do
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		mkswap /dev/zram$i > err.log 2>&1
		if [ $? -ne 0 ]; then
			cat err.log
			echo "FAIL mkswap /dev/zram$1 failed"
		fi

		swapon /dev/zram$i > err.log 2>&1
		if [ $? -ne 0 ]; then
			cat err.log
			echo "FAIL swapon /dev/zram$1 failed"
		fi

		echo "done with /dev/zram$i"
		dev_makeswap=$i
	done

	echo "zram making zram mkswap and swapon: OK"
}

zram_swapoff()
{
	local i=
<<<<<<< HEAD
	for i in $(seq 0 $dev_makeswap); do
=======
	for i in $(seq $dev_start $dev_end); do
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		swapoff /dev/zram$i > err.log 2>&1
		if [ $? -ne 0 ]; then
			cat err.log
			echo "FAIL swapoff /dev/zram$i failed"
		fi
	done
	dev_makeswap=-1

	echo "zram swapoff: OK"
}

zram_makefs()
{
<<<<<<< HEAD
	local i=0
=======
	local i=$dev_start
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	for fs in $zram_filesystems; do
		# if requested fs not supported default it to ext2
		which mkfs.$fs > /dev/null 2>&1 || fs=ext2

		echo "make $fs filesystem on /dev/zram$i"
		mkfs.$fs /dev/zram$i > err.log 2>&1
		if [ $? -ne 0 ]; then
			cat err.log
			echo "FAIL failed to make $fs on /dev/zram$i"
		fi
		i=$(($i + 1))
		echo "zram mkfs.$fs: OK"
	done
}

zram_mount()
{
	local i=0
<<<<<<< HEAD
	for i in $(seq 0 $(($dev_num - 1))); do
=======
	for i in $(seq $dev_start $dev_end); do
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		echo "mount /dev/zram$i"
		mkdir zram$i
		mount /dev/zram$i zram$i > /dev/null || \
			echo "FAIL mount /dev/zram$i failed"
		dev_mounted=$i
	done

	echo "zram mount of zram device(s): OK"
}
