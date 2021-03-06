/**************************** settings.cpp ***************************

Dialog to select program settings

Copyright (C) 2013-2014
by: Andrew J. Bibb
License: MIT 

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"),to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions: 

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
***********************************************************************/ 


# include <QtCore/QDebug>

# include "./code/settings/settings.h"
# include "./code/resource.h"

// constructor
// Most of the interface is defined in the ui
Settings::Settings(QWidget *parent)
    : QDialog(parent)
{	
  // setup the user interface
  ui.setupUi(this);	
  
  // read the settings
  settings = new QSettings(ORG, APP, this);
  
  // save the preferences in a class data member
	settings->beginGroup("Preferences");
	usestartoptions = settings->value("use_startoptions").toBool();
	ui.groupBox_startoptions->setEnabled(usestartoptions);
	usestate = settings->value("retain_state").toBool();
	useplaylist = settings->value("retain_playlist").toBool();
	settings->endGroup();
	
	// seed dialog values
	ui.checkBox_usestartoptions->setChecked(usestartoptions);
	ui.checkBox_retainstate->setChecked(usestate);
	ui.checkBox_retainplaylist->setChecked(useplaylist);
	
	settings->beginGroup("StartOptions");
	ui.checkBox_fullscreen->setChecked(settings->value("start_fullscreen").toBool() );
	ui.checkBox_gui->setChecked(settings->value("start_gui").toBool() );
	ui.checkBox_icontheme->setChecked(settings->value("use_icon_theme").toBool() );
	if (ui.checkBox_icontheme->isChecked() ) ui.lineEdit_icontheme->setEnabled(true);
	ui.lineEdit_icontheme->setText(settings->value("icon_theme_name").toString() );
	ui.spinBox_loglevel->setValue(settings->value("log_level").toInt() );
	ui.checkBox_visualizer->setChecked(settings->value("start_visualizer").toBool() );
	ui.checkBox_subtitles->setChecked(settings->value("start_subtitles").toBool() );
	ui.checkBox_streambuffering->setChecked(settings->value("use_stream_buffering").toBool() );
	ui.checkBox_downloadbuffering->setChecked(settings->value("use_download_buffering").toBool() );
	ui.lineEdit_audiocd->setText(settings->value("audio_cd_drive").toString() );
	ui.lineEdit_dvd->setText(settings->value("dvd_drive").toString() );
	ui.spinBox_connectionspeed->setValue(settings->value("connection_speed").toInt() );
	settings->endGroup();
		
	return;  
}  

// Function to save GUI start options and preferences
void Settings::writeSettings()
{
  settings->beginGroup("Preferences");
  settings->setValue("use_startoptions", ui.checkBox_usestartoptions->isChecked() );
  settings->setValue("retain_state", ui.checkBox_retainstate->isChecked() );
  settings->setValue("retain_playlist", ui.checkBox_retainplaylist->isChecked() );
  settings->endGroup();

  settings->beginGroup("StartOptions");
  settings->setValue("start_fullscreen", ui.checkBox_fullscreen->isChecked() );
	settings->setValue("start_gui", ui.checkBox_gui->isChecked() );  
  settings->setValue("use_icon_theme", ui.checkBox_icontheme->isChecked() );
  settings->setValue("icon_theme_name", ui.lineEdit_icontheme->text()  );
  settings->setValue("log_level", ui.spinBox_loglevel->value() );
  settings->setValue("start_visualizer", ui.checkBox_visualizer->isChecked() );
  settings->setValue("start_subtitles", ui.checkBox_subtitles->isChecked() );
  settings->setValue("use_stream_buffering", ui.checkBox_streambuffering->isChecked() );
  settings->setValue("use_download_buffering", ui.checkBox_downloadbuffering->isChecked() );
  settings->setValue("audio_cd_drive", ui.lineEdit_audiocd->text() );
  settings->setValue("dvd_drive", ui.lineEdit_dvd->text() );
  settings->setValue("connection_speed", ui.spinBox_connectionspeed->value() );
  settings->endGroup();
  
  return;
}

//
// Function to save the geometry of a window
void Settings::saveElementGeometry(const QString& elem, const bool& vis, const QSize& size, const QPoint& point)
{
	settings->beginGroup("State");
	settings->setValue(QString("%1_vis").arg(elem), vis);
	settings->setValue(QString("%1_size").arg(elem), size);
	settings->setValue(QString("%1_pos").arg(elem), point);
	settings->endGroup();
}

//
// Function to restore the geometry of a window
void Settings::restoreElementGeometry(const QString& elem, QWidget* win)
{
	settings->beginGroup("State");	
	if (settings->value(QString("%1_vis").arg(elem)).toBool() ) {
		win->show();
		win->resize(settings->value(QString("%1_size").arg(elem)).toSize() );
		win->move(settings->value(QString("%1_pos").arg(elem)).toPoint() );
	}
	settings->endGroup();
}

//
// Function to return a start option as a QVariant
QVariant Settings::getStartOption(const QString& elem)
{
	QVariant v;
	v.clear();
	
	settings->beginGroup("StartOptions");
	v = settings->value(elem);
	settings->endGroup();
	
	return v;	
}

//
// Function to save the playlist
void Settings::savePlaylist(const QStringList& pl)
{
	settings->beginGroup("Playlist");
	settings->setValue("entries", pl);
	settings->endGroup();
}

//
// Function to return the playlist
QStringList Settings::getPlaylist()
{
	// string list to return
	QStringList sl;
	sl.clear();
	
	settings->beginGroup("Playlist");
	sl = settings->value("entries").toStringList();
	settings->endGroup();
	
	return sl;
}


