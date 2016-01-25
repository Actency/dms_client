DMS client
==========

DMS means Drupal Management System.
It is composed of this client probe and of a server that gathers information from all probes and generates reports.

This client exposes some URLs to be called to execute actions such as cache clearing and user login.
An URL to fetch information about this current drupal installation is also exposed.


Configuration
-------------

Install the module and go to the configuration page at : admin/config/system/dms_client/settings
Set the Secret token given by the server for this site.
You will then allow the server to fetch data from this drupal installation.


Endpoints
---------

There are two main endpoints and two more for their descriptions.
For each call you have to specify the token secret to allow access.

Reports :
 - dms/report/generate : generates a website report with given parameters : mode or specifics.
 - dms/report/describe : describe all available modes and tasks for report generation.
 
Actions :
 - dms/action/%key/execute : execute the action with the given key.
 - dms/action/describe : describe all available actions with their keys.
 
 
Extend the module
-----------------

To let other modules extend this, some hooks are available.
You can for example alter the list of modes/tasks for report generation, and also implements new actions.
See dms_client.api.php file.