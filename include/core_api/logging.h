/****************************************************************************
 *      logging.h: YafaRay Logging control
 *      This is part of the yafray package
 *      Copyright (C) 2010 Rodrigo Placencia Vazquez for original Console_Verbosity file
 *		Copyright (C) 2016 David Bluecame for all changes to convert original
 * 		console output classes/objects into full Logging classes/objects
 * 		and the Log and HTML file saving.
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
 
#ifndef Y_CONSOLE_VERBOSITY_H
#define Y_CONSOLE_VERBOSITY_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

__BEGIN_YAFRAY

enum
{
	VL_MUTE = 0,
	VL_ERROR,
	VL_WARNING,
	VL_PARAMS,
	VL_INFO,
	VL_VERBOSE,
	VL_DEBUG,
};

class YAFRAYCORE_EXPORT logEntry_t
{
	friend class yafarayLog_t;
	
	public:
		logEntry_t(std::time_t datetime, int verb_level, std::string description):eventDateTime(datetime),mVerbLevel(verb_level),eventDescription(description) {}

	protected:
		std::time_t eventDateTime;
		int mVerbLevel;
		std::string eventDescription;
};
	

class YAFRAYCORE_EXPORT yafarayLog_t
{
	public:
		yafarayLog_t() {}
		
		~yafarayLog_t() {}

		void setConsoleMasterVerbosity(const std::string &strVLevel);
		void setLogMasterVerbosity(const std::string &strVLevel);

		void setSaveLog(bool save_log) { mSaveLog = save_log; }
		void setSaveHTML(bool save_html) { mSaveHTML = save_html; }
		void setParamsBadgePosition(const std::string &badgePosition);
		void setLoggingTitle(const std::string &title) { mLoggingTitle = title; }
		void setLoggingAuthor(const std::string &author) { mLoggingAuthor = author; }
		void setLoggingContact(const std::string &contact) { mLoggingContact = contact; }
		void setLoggingComments(const std::string &comments) { mLoggingComments = comments; }
		void setLoggingCustomIcon(const std::string &iconPath) { mLoggingCustomIcon = iconPath; }
		void setImagePath(const std::string &path) { mImagePath = path; }
		void appendAANoiseSettings(const std::string &aa_noise_settings);
		void appendRenderSettings(const std::string &render_settings);
		void setDrawAANoiseSettings(bool draw_noise_settings) { drawAANoiseSettings = draw_noise_settings; }
		void setDrawRenderSettings(bool draw_render_settings) { drawRenderSettings = draw_render_settings; }

		bool getUseParamsBadge() { return mDrawParams; }
		bool isParamsBadgeTop() { return mParamsBadgeTop; }
		std::string getLoggingTitle() const { return mLoggingTitle; }
		std::string getLoggingAuthor() const { return mLoggingAuthor; }
		std::string getLoggingContact() const { return mLoggingContact; }
		std::string getLoggingComments() const { return mLoggingComments; }
		std::string getLoggingCustomIcon() const { return mLoggingCustomIcon; }
		std::string getAANoiseSettings() const { return mAANoiseSettings; }
		std::string getRenderSettings() const { return mRenderSettings; }
		bool getDrawAANoiseSettings() { return drawAANoiseSettings; }
		bool getDrawRenderSettings() { return drawRenderSettings; }
		int getBadgeHeight() const;
		
		void saveTxtLog(const std::string &name);
		void saveHtmlLog(const std::string &name);
		void clearMemoryLog();
		void clearAll();
		void splitPath(const std::string &fullFilePath, std::string &basePath, std::string &baseFileName, std::string &extension);
		yafarayLog_t &out(int verbosity_level);
		void setConsoleMasterVerbosity(int vlevel);
		void setLogMasterVerbosity(int vlevel);
		std::string printTime(std::time_t datetime) const;
		std::string printDate(std::time_t datetime) const;
		int vlevel_from_string(std::string strVLevel) const;

		template <typename T>
		yafarayLog_t & operator << ( const T &obj )
		{
			std::ostringstream tmpStream;
			tmpStream << obj;

			if(mVerbLevel <= mConsoleMasterVerbLevel) std::cout << obj;
			if(mVerbLevel <= mLogMasterVerbLevel && !m_MemoryLog.empty()) m_MemoryLog.back().eventDescription += tmpStream.str();
			return *this;
		}

		yafarayLog_t & operator << ( std::ostream& (obj)(std::ostream&) )
		{
			std::ostringstream tmpStream;
			tmpStream << obj;

			if(mVerbLevel <= mConsoleMasterVerbLevel) std::cout << obj;
			if(mVerbLevel <= mLogMasterVerbLevel && !m_MemoryLog.empty()) m_MemoryLog.back().eventDescription += tmpStream.str();
			return *this;
		}

	protected:
		int mVerbLevel = VL_INFO;
		int mConsoleMasterVerbLevel = VL_INFO;
		int mLogMasterVerbLevel = VL_VERBOSE;
		std::vector<logEntry_t> m_MemoryLog;	//Log entries stored in memory
		std::string mImagePath = "";
		bool mParamsBadgeTop = true;//If enabled, draw badge in the top of the image instead of the bottom
		bool mDrawParams = false;	//Enable/disable drawing params badge in exported images
		bool mSaveLog = false;		//Enable/disable text log file saving with exported images
		bool mSaveHTML = false;		//Enable/disable HTML file saving with exported images
		std::string mLoggingTitle;
		std::string mLoggingAuthor;
		std::string mLoggingContact;
		std::string mLoggingComments;
		std::string mLoggingCustomIcon;		
		std::string mAANoiseSettings;
		std::string mRenderSettings;
		bool drawAANoiseSettings = true;
		bool drawRenderSettings = true;
};

extern YAFRAYCORE_EXPORT yafarayLog_t yafLog;

__END_YAFRAY

#endif
