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