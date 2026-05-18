# :80 S3 reverse proxy for SeaweedFS. Written to /etc/nginx/conf.d/s3-proxy.conf
# by manifest `configureLB`. SigV4-safe directives live in s3-proxy.inc so the
# :443 server (created by scripts/deployHook.js after Let's Encrypt issues the
# cert) reuses the exact same contract. TLS terminates at the LB.

server {
    listen 80 default_server;
    server_name _;

    include /etc/nginx/conf.d/s3-proxy.inc;
}
