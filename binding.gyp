{
    "targets": [
        {
            "target_name": "Chroma",
            "sources": [ "Chroma.cc","NodeKeyboard.cc", "SDK.cc"],
            "include_dirs" : [
 	 			"<!(node -e \"require('nan')\")"
			]
        }
    ],
}