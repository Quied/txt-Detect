#pragma once

namespace SELECT {
	enum Condition {
		CONTINUE = 1,
		REMOVE,
		NEXT
	};
}

enum Condition {
	FAIL,
	WAIT,
	NEXT,
	REMOVE,
	CLEAR,
	STOP,
	MINUTE = 60
};
