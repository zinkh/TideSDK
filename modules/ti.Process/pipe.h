/**
 * Appcelerator Titanium - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PIPE_H_
#define _PIPE_H_

#include <kroll/kroll.h>
#include <queue>
#include <Poco/Thread.h>
#include <Poco/RunnableAdapter.h>

namespace ti
{
	class Pipe;
	typedef AutoPtr<Pipe> AutoPipe;

	class Pipe : public KEventObject
	{
	public:
		static AutoPipe CreatePipe();
		
		Pipe(const char *type = "Process.Pipe");
		virtual ~Pipe();

		virtual AutoPtr<Blob> Read(int bufsize=-1);
		virtual AutoPtr<Blob> ReadLine();
		virtual void Close();
		virtual bool IsClosed();
		virtual int Write(AutoPtr<Blob> data);
		void Write(char *data, int length);
		virtual void Flush();

		int GetSize();
		const char* GetBuffer();

		void DataReady(AutoPipe pipe = NULL);
		void Attach(SharedKObject other);
		void Detach();
		bool IsAttached();
		
		void SetAsyncOnRead(bool asyncOnRead) { this->asyncOnRead = asyncOnRead; }
		AutoPipe Clone();

		virtual void Closed();
		void SetOnClose(SharedKMethod onClose);
		
	protected:
		int FindFirstLineFeed(char *data, int length, int *charsToErase);
		void FireEvents();
		
		void _Close(const ValueList& args, SharedValue result);
		void _IsClosed(const ValueList& args, SharedValue result);
		void _SetOnClose(const ValueList& args, SharedValue result);
		void _Read(const ValueList& args, SharedValue result);
		void _ReadLine(const ValueList& args, SharedValue result);
		void _IsJoined(const ValueList& args, SharedValue result);
		void _Attach(const ValueList& args, SharedValue result);
		void _Detach(const ValueList& args, SharedValue result);
		void _IsAttached(const ValueList& args, SharedValue result);
		void _Write(const ValueList& args, SharedValue result);
		void _Flush(const ValueList& args, SharedValue result);

		SharedKMethod *onClose;
		SharedKObject* attachedOutput;
		Logger *logger;
		bool asyncOnRead;
		Poco::Mutex mutex;
		bool closed, asyncRead;

		Poco::Mutex buffersMutex;
		std::queue<AutoBlob> buffers;
		Poco::Thread* eventsThread;
		Poco::RunnableAdapter<Pipe>* eventsThreadAdapter;

	};
}

#endif
