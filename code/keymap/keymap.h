/**************************** keymap.h *****************************

Code to manage the mappings from key presses to commands. 

Copyright (C) 2014-2014
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

# ifndef KEYMAP_H
# define KEYMAP_H

# include <QObject>
# include <QWidget>
# include <QString>
# include <QStringList>
# include <QKeyEvent>
# include <QMap>
# include <QKeySequence>
# include <QList>


//	This class is based on a QObject
class KeyMap : public QObject
{
  Q_OBJECT

  public:
    KeyMap(QObject*);

  public slots:
		QList<QKeySequence> getKeySequence(const QString&);
		QString getCheatSheet();  

  private:
		// members 
		QMap<QString, QList<QKeySequence> > usermap;
		QString filepath;
	       
	// functions
		void makeLocalFile();
		QStringList readTextFile(const char*);

};

#endif

