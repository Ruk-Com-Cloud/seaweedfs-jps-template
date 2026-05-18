# SeaweedFS S3 ติดตั้งสำเร็จ ✅ (เฟส 1 จาก 2)

บริการ SeaweedFS S3 ของคุณทำงานแล้วบน **HTTP** ชั่วคราว ขั้นต่อไปคือผูกโดเมน + เปิด HTTPS

## ข้อมูลการเข้าถึง (ชั่วคราว)

- **S3 endpoint (ชั่วคราว):** `http://${nodes.bl.address}/`
- **Access Key:** `${globals.S3_ACCESS_KEY}`
- **Secret Key:** `${globals.S3_SECRET_KEY}`
- **Addressing:** ใช้ **path-style เท่านั้น** — ตั้ง client เป็น force-path-style
  (เช่น `aws --endpoint-url http://${nodes.bl.address} s3 ls`)

> ⚠️ เก็บ Secret Key ให้ปลอดภัย — จะไม่แสดงซ้ำ

## ขั้นตอนถัดไป — ผูกโดเมนและเปิด HTTPS

**1. Public IP ที่ได้รับ:** `${nodes.bl.extIPs}`

**2. สร้าง DNS record** ที่ผู้ให้บริการโดเมนของคุณ:

| Type | Name | Value | TTL |
|---|---|---|---|
| A | `${settings.externalDomain}` | `${nodes.bl.extIPs}` | 300 |

**3. รอ DNS propagate** แล้วตรวจ: `dig +short ${settings.externalDomain}` ต้องได้ `${nodes.bl.extIPs}`

**4. เปิดแท็บ Add-Ons → กดปุ่ม "Bind SSL / Issue Certificate"** — ระบบจะตรวจ DNS, ออกใบรับรอง, สลับเป็น `https://${settings.externalDomain}/`

---

ℹ️ ถ้าไม่แนบ Public IP หรือไม่ใส่โดเมน — endpoint ชั่วคราวด้านบนใช้ได้เลย ตั้ง SSL ภายหลังผ่านปุ่มเดียวกันได้

📚 เปลี่ยนเวอร์ชันผ่านปุ่ม **"Change Version"** (สำรองข้อมูลก่อนเสมอ ข้อมูลใน volume ถูกรักษาไว้)
