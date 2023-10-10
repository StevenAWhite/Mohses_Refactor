# Supervisor Scripts 

Mohses uses Supervisor scripts for managing subservices of a mohses installation. CMake 
will generate configured Mohses scripts for each built module, but you may require some 
additional changes depending on your system configuration. The following is intended to 
introduce to key supervisor concepts


# Example Script
```
   [program:mohses_physiology_manager]
   autostart=false
   autorestart=true
   directory=/usr/local/bin
   command=/usr/local/bin/mohses_physiology_manager -a
   priority=10
   numprocs=1
   user=mohses
   redirect_stderr=true
   stdout_logfile=/usr/local/bin/logs/mohses_physiology_manager.log
```

Each script contains the name of the service in Supervisor. The `directory` it executs 
in the  `command` to be execute to initiate the service and the `stdout_logfile` 
location.

#Using Supervisor

To install supervisor on Debian based systems run the following command. 

```
sudo apt update && sudo apt install supervisor
```

You can check supervsiors status with the following command. 

```
sudo systemctl status supervisor
```

Supervisor scripts should be placed in `/etc/supervisor/conf.d` anytime you update these 
scripts you may run the following to have supervisor reprocess them.

```
supervisorctl reread
```

At anytime you can use `supervisorctl` for additional commands for each service. For 
further reading see the 
[http://supervisord.org/running.html#running-supervisorctl](Manual).

# Installing Supervisor Scripts
After installing this package CMAKE will place modified scripts in `CMAKE_INSTALL_PREFIX/share/mohses/supervisor`. Copying these scripts to `/etc/supervisor/conf.d` will allow you to manage modules as they were installed. YOu will need to create an `mohses` user and group  for controlling services or modified the configuration accordingly.  If you require additional changes you can modify the templates included in this folder or the ones installed to meet your systems specific needs.


