#ofxSensuHeartbeat

A simple addon to be used in conjunction with ofxSensu.

Sends a still alive message with the format `'{"name": "ofxApp-Heartbeat", "ttl": 2, "handlers": ["remediator"], "output":"The app is still alive", "remediation": {"kill_ofx_application": { "occurrences": [1], "severities": [1] }}}`
Every `ttl` / 2  seconds.