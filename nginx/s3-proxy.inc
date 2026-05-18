# Shared SigV4-safe S3 proxy directives — included by BOTH the :80 server
# (s3-proxy.conf.tpl) and the :443 server written by the Let's Encrypt
# deployHook (scripts/deployHook.js). One file = HTTPS gets the exact same
# SigV4-safe contract as HTTP (the LE add-on does NOT write our vhost —
# verified jelastic-jps/lets-encrypt ssl-manager.js delegates 443 to jem ssl/SLB).
#
# __CP_HOST__ / __S3_PORT__ substituted at install time.
# RULE: transparent byte/header pipe, never a normalizing cache.

client_max_body_size 0;          # NGINX 1MB default -> 413 on large/multipart
merge_slashes off;               # do not collapse // in keys (signed URI)
ignore_invalid_headers off;      # S3 uses headers NGINX may otherwise drop

# SeaweedFS S3 health: GET /healthz on the S3 port (verified).
# Do NOT probe "/" when S3 auth is enabled — it returns 403 (seaweedfs#8243).
location = /healthz {
    proxy_pass http://__CP_HOST__:__S3_PORT__;
    access_log off;
}

location / {
    proxy_pass http://__CP_HOST__:__S3_PORT__;

    # SeaweedFS S3 validates SigV4 against the incoming Host; path-style +
    # preserved Host => presigned/SigV4 correct. Also pass X-Forwarded-*.
    proxy_set_header Host               $http_host;
    proxy_set_header X-Real-IP          $remote_addr;
    proxy_set_header X-Forwarded-For    $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto  $scheme;
    proxy_set_header X-Forwarded-Host   $http_host;

    proxy_buffering         off;     # stream large GETs
    proxy_request_buffering off;     # don't corrupt aws-chunked streaming SigV4
    proxy_http_version      1.1;
    proxy_read_timeout      300s;
    proxy_send_timeout      300s;
    proxy_connect_timeout   75s;

    chunked_transfer_encoding off;   # response side only
    proxy_redirect off;
    # Authorization + x-amz-* forwarded unmodified (NGINX default).
}
