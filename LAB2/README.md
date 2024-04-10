# lab2
## task 1
1. setting
	1. set the Nginx
		1. install nginx: ```sudo apt install nginx```
			* NOTE: nginx's system file
				* /usr/sbin/nginx - This is the location of the Nginx executable. This file is the actual binary that runs the Nginx server.
				* /etc/nginx/ - This directory holds the Nginx configuration files, including nginx.conf (the main configuration file) and any other configuration files for Nginx modules and sites (often in subdirectories like sites-available and sites-enabled).
				* /usr/share/nginx/ - This directory contains static files and resources for Nginx. For example, it may contain the default HTML files used by Nginx.
				* /var/log/nginx/ - Log files for Nginx are stored here. These include access logs and error logs.
				* /var/www/html/ - This is the default directory where the web files to be served by Nginx are stored. You might place your HTML, CSS, and other files here.
			* NOTE: nginx's server configuration setting(under /etc/)
				* /etc/nginx/sites-available/default
					* defin root at ```/var/www/html```
				* /etc/nginx/nginx.conf
		2. pull two html files which provided by lab2 to root path of nginx server(```/var/www/html```): 
			* NOTE: it would be different root path of nginx because of different install tool. you can use ```grep -r 'root' /etc/nginx/sites-available/``` to find where the root path is defined
				* the default root path by apt is at "/var/www/html/"
			* ```sudo mkdir /var/www/html/safe```
			* ```sudo cp ./safe_index.html /var/www/html/safe/index.html```
			* ```sudo mkdir /var/www/html/unsafe```
			* ```sudo cp ./unsafe_index.html /var/www/html/unsafe/index.html```

	3. set Apparmor
		1. install apparmor: ```sudo apt install apparmor-easyprof apparmor-notify apparmor-utils```
		2. create the profile by  ```sudo aa-genprof [APP_PATH]```
			* here to restrict nginx server, you can use ```sudo aa-genprof /usr/sbin/nginx```
		3. modify the apparmor profile to desired policy, you can use ```sudo nano /etc/apparmor.d/usr.sbin.nginx```
			* ```
				#include <tunables/global>
				/usr/sbin/nginx {
					#include <abstractions/apache2-common>
					#include <abstractions/base>
					#include <abstractions/nis>

					capability dac_override,
					capability dac_read_search,
					capability net_bind_service,
					capability setgid,
					capability setuid,

					deny /var/www/html/unsafe/* r,
					/** rw,
				}
			```
			1. the apparmor deny all the files and services access in default, and there are a lot of access requirement from nginx server. fro convenience, I allow all the files and service to be accessed except to /var/www/html/unsafe/index.html
			2. this profile file is modified from https://www.digitalocean.com/community/tutorials/how-to-create-an-apparmor-profile-for-nginx-on-ubuntu-14-04, but it not enough for my nginx
		4. reload the profile to kernel: ```sudo apparmor_parser -r /etc/apparmor.d/usr.sbin.nginx```
		5. enable the apparmor:
			1. enforce mode: ```sudo aa-enforce /etc/apparmor.d/usr.sbin.nginx```
			2. complain mode: ```sudo aa-complain /etc/apparmor.d/usr.sbin.nginx```
		6. disable and delete the apparmor
			* ```sudo systemctl reload apparmor```
			* ```sudo aa-disable /etc/apparmor.d/usr.sbin.nginx```
			* ```sudo rm /etc/apparmor.d/usr.sbin.nginx```
			* ??
				* ```sudo systemctl stop apparmor```
				* ```sudo systemctl disable apparmor```

		7. check the apparmor status: ```sudo aa-status```
		* NOTE: if there is denied permission issue, you can run ```sudo cat /var/log/kern.log``` to ckeck if there is the lack permission.
2. run nginx
* start nuginx server: ```sudo systemctl start nginx```
* check state of nginx server: ```sudo systemctl status nginx```
* restart nuginx server: ```sudo systemctl restart nginx```
* stop nuginx server:```sudo systemctl stop nginx```

## task 2
1. ```sudo apt-get update && apt-get install docker-compose```
2. ```docker build -t nspj:latest . ```
3. ```docker-compose up```










