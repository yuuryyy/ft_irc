# 💬 ft_irc

A custom-built Internet Relay Chat (IRC) server written entirely in **C++98**. This project dives deep into network programming, focusing on the TCP/IP stack, socket manipulation, and handling multiple concurrent client connections asynchronously.

---

## 📖 About The Project

Before REST APIs and modern messaging apps, the internet communicated via IRC. The goal of `ft_irc` is to recreate a fully functional IRC server capable of handling real-world IRC clients (like `irssi`, `WeChat`, or `nc`). 

Beyond just parsing text, this project is a foundational exercise in backend infrastructure. It requires a robust understanding of non-blocking I/O, file descriptor multiplexing (using `poll()`), and strict adherence to networking protocols (RFC 1459 / 2812).

### 🎯 Core Objectives
* Master **Socket Programming** in C/C++ (`socket`, `bind`, `listen`, `accept`).
* Implement I/O Multiplexing to handle multiple clients concurrently without multi-threading.
* Parse and respond to standardized network protocols.
* Build a resilient architecture capable of handling partial data, dropped connections, and malicious inputs without crashing.

---

## ✨ Features & Implemented Commands

The server successfully handles client authentication, messaging, and complex channel management.

### User Management
* **Authentication:** Connection requires a server password.
* **Registration:** Handles `NICK` and `USER` commands to establish identity.

### Channel Operations
* **`JOIN`**: Create or enter existing channels.
* **`PART`**: Leave a channel.
* **`PRIVMSG`**: Send private messages to individual users or broadcast to an entire channel.

### 🛡️ Operator Commands
Channel operators have elevated privileges to manage their rooms:
* **`KICK`**: Forcibly remove a user from the channel.
* **`INVITE`**: Invite a user to a private or regular channel.
* **`TOPIC`**: View or change the channel's topic.
* **`MODE`**: Change channel settings:
  * `i`: Invite-only channel.
  * `t`: Topic restricted to operators.
  * `k`: Set/remove a channel password (key).
  * `o`: Grant/revoke operator privileges.
  * `l`: Set a user limit on the channel.

---

## 🏗️ Technical
