

                              /[-])//  ___
                         __ --\ `_/~--|  / \
                       /_-/~~--~~ /~~~\\_\ /\
                       |  |___|===|_-- | \ \ \
     _/~~~~~~~~|~~\,   ---|---\___/----|  \/\-\
     ~\________|__/   / // \__ |  ||  / | |   | |
              ,~-|~~~~~\--, | \|--|/~|||  |   | |
              [3-|____---~~ _--'==;/ _,   |   |_|
                          /   /\__|_/  \  \__/--/
                         /---/_\  -___/ |  /,--|
                         /  /\/~--|   | |  \///
                        /  / |-__ \    |/
                       |--/ /      |-- | \
                      \^~~\\/\      \   \/- _
                       \    |  \     |~~\~~| \
                        \    \  \     \   \  | \
                          \    \ |     \   \    \
                           |~~|\/\|     \   \   |
                          |   |/         \_--_- |\
                          |  /            /   |/\/
                           ~~             /  /
                                         |__/


               ==== DVS PTP CLOCK MITM =====

    Targets:

	h|help		shows this help.txt
	b|build		compiles code
	c|clean		remove built code
	dir		echo directory for manual intervention

    The following targets require sudo, ex 'sudo make install'

	install		sets up man-in-the-middle
	uninstall	remove man-in-the-middle


Installation notes
---

Creating and using the installation script requires you to work on the terminal and to have the essential command line tools installed.

1. Open up the terminal by starting the `Terminal.app` in `Applications > Utilities` 
2. Change to the directory to where you saved the (unzipped) files of this repository. Ex if the files are located on your desktop in a folder dvs-ptp-mitm type `cd ~/Desktop/dcs-ptp-mitm`.
3. If you don't know wether you have the command line tools installed type `xcode-select --install`
4. When you thus type `make` you should see the contents of this readme printed onto the screen.
5. To create/compile the source code to a binary type `make build`. This should create a file called ptp-mitm in the same folder.
6. To install the binary type `sudo make install`

7. To uninstall again type `sudo make uninstall`

To simplify repeated installation (step 6) and uninstallation (step 7) you can also run the two automator apps `Activate / Deactivate DVS-PTP-MITM`.


Application note
---
As you can also clearly see when looking at the source code `ptp-mitm.c` what happens is that the new executable calls the original ptp executable with the exact same arguments *except* for the `-s` option which tells the ptp service to act as slave only.

That is, by removing this option the ptp service is allowed to also become the (grand)master clock.

Yes, this option was available from the get-go, but by default it is run slave-mode only.
