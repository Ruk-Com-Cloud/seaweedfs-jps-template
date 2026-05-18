/**
 * onBeforeInit — guard the EXPERIMENTAL cluster path only.
 *
 * The image is NOT set here: node topology is evaluated before script-set
 * globals exist (routing the image through an onBeforeInit global yields a
 * literal "${globals.SEAWEEDFS_IMAGE}:latest" -> "invalid reference format").
 * It is resolved directly from the configs/vers.yaml mixin globals in
 * nodes.cp.image.
 *
 * Cloud Scripting JS: return { result: 0 } to continue; result != 0 aborts.
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

return { result: 0 };
