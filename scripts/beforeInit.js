/**
 * onBeforeInit — pin the SeaweedFS image from configs/vers.yaml globals and
 * guard the EXPERIMENTAL cluster path.
 *
 * Cloud Scripting JS: return { result: 0 } to continue; result != 0 aborts.
 * nodeCount only exists when topology == cluster (showIf child of topology).
 */

var topology  = '${settings.topology}';
var nodeCountS = '${settings.nodeCount:0}';

if (topology === 'cluster') {
	var n = parseInt(nodeCountS, 10);
	if (isNaN(n) || n < 3) {
		return {
			result: 4001,
			type: 'warning',
			message: 'SeaweedFS cluster requires at least 3 nodes. Choose "single" ' +
			         'for the simplest production setup, or pick a cluster size.'
		};
	}
}

return {
	result: 0,
	onAfterReturn: {
		setGlobals: {
			SEAWEEDFS_IMAGE: '${globals.seaweedfs_image_repo}:${globals.seaweedfs_default_tag}'
		}
	}
};
