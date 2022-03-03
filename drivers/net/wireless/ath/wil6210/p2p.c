/*
 * Copyright (c) 2014-2017 Qualcomm Atheros, Inc.
<<<<<<< HEAD
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "wil6210.h"
#include "wmi.h"

#define P2P_WILDCARD_SSID "DIRECT-"
#define P2P_DMG_SOCIAL_CHANNEL 2
#define P2P_SEARCH_DURATION_MS 500
#define P2P_DEFAULT_BI 100

<<<<<<< HEAD
static int wil_p2p_start_listen(struct wil6210_vif *vif)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	struct wil_p2p_info *p2p = &vif->p2p;
=======
static int wil_p2p_start_listen(struct wil6210_priv *wil)
{
	struct wil_p2p_info *p2p = &wil->p2p;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	u8 channel = p2p->listen_chan.hw_value;
	int rc;

	lockdep_assert_held(&wil->mutex);

<<<<<<< HEAD
	rc = wmi_p2p_cfg(vif, channel, P2P_DEFAULT_BI);
=======
	rc = wmi_p2p_cfg(wil, channel, P2P_DEFAULT_BI);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	if (rc) {
		wil_err(wil, "wmi_p2p_cfg failed\n");
		goto out;
	}

<<<<<<< HEAD
	rc = wmi_set_ssid(vif, strlen(P2P_WILDCARD_SSID), P2P_WILDCARD_SSID);
=======
	rc = wmi_set_ssid(wil, strlen(P2P_WILDCARD_SSID), P2P_WILDCARD_SSID);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	if (rc) {
		wil_err(wil, "wmi_set_ssid failed\n");
		goto out_stop;
	}

<<<<<<< HEAD
	rc = wmi_start_listen(vif);
=======
	rc = wmi_start_listen(wil);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	if (rc) {
		wil_err(wil, "wmi_start_listen failed\n");
		goto out_stop;
	}

	INIT_WORK(&p2p->discovery_expired_work, wil_p2p_listen_expired);
	mod_timer(&p2p->discovery_timer,
		  jiffies + msecs_to_jiffies(p2p->listen_duration));
out_stop:
	if (rc)
<<<<<<< HEAD
		wmi_stop_discovery(vif);
=======
		wmi_stop_discovery(wil);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

out:
	return rc;
}

bool wil_p2p_is_social_scan(struct cfg80211_scan_request *request)
{
	return (request->n_channels == 1) &&
	       (request->channels[0]->hw_value == P2P_DMG_SOCIAL_CHANNEL);
}

<<<<<<< HEAD
int wil_p2p_search(struct wil6210_vif *vif,
		   struct cfg80211_scan_request *request)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	int rc;
	struct wil_p2p_info *p2p = &vif->p2p;
=======
void wil_p2p_discovery_timer_fn(ulong x)
{
	struct wil6210_priv *wil = (void *)x;

	wil_dbg_misc(wil, "p2p_discovery_timer_fn\n");

	schedule_work(&wil->p2p.discovery_expired_work);
}

int wil_p2p_search(struct wil6210_priv *wil,
		   struct cfg80211_scan_request *request)
{
	int rc;
	struct wil_p2p_info *p2p = &wil->p2p;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	wil_dbg_misc(wil, "p2p_search: channel %d\n", P2P_DMG_SOCIAL_CHANNEL);

	lockdep_assert_held(&wil->mutex);

	if (p2p->discovery_started) {
		wil_err(wil, "search failed. discovery already ongoing\n");
		rc = -EBUSY;
		goto out;
	}

<<<<<<< HEAD
	rc = wmi_p2p_cfg(vif, P2P_DMG_SOCIAL_CHANNEL, P2P_DEFAULT_BI);
=======
	rc = wmi_p2p_cfg(wil, P2P_DMG_SOCIAL_CHANNEL, P2P_DEFAULT_BI);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	if (rc) {
		wil_err(wil, "wmi_p2p_cfg failed\n");
		goto out;
	}

<<<<<<< HEAD
	rc = wmi_set_ssid(vif, strlen(P2P_WILDCARD_SSID), P2P_WILDCARD_SSID);
=======
	rc = wmi_set_ssid(wil, strlen(P2P_WILDCARD_SSID), P2P_WILDCARD_SSID);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	if (rc) {
		wil_err(wil, "wmi_set_ssid failed\n");
		goto out_stop;
	}

	/* Set application IE to probe request and probe response */
<<<<<<< HEAD
	rc = wmi_set_ie(vif, WMI_FRAME_PROBE_REQ,
=======
	rc = wmi_set_ie(wil, WMI_FRAME_PROBE_REQ,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
			request->ie_len, request->ie);
	if (rc) {
		wil_err(wil, "wmi_set_ie(WMI_FRAME_PROBE_REQ) failed\n");
		goto out_stop;
	}

	/* supplicant doesn't provide Probe Response IEs. As a workaround -
	 * re-use Probe Request IEs
	 */
<<<<<<< HEAD
	rc = wmi_set_ie(vif, WMI_FRAME_PROBE_RESP,
=======
	rc = wmi_set_ie(wil, WMI_FRAME_PROBE_RESP,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
			request->ie_len, request->ie);
	if (rc) {
		wil_err(wil, "wmi_set_ie(WMI_FRAME_PROBE_RESP) failed\n");
		goto out_stop;
	}

<<<<<<< HEAD
	rc = wmi_start_search(vif);
=======
	rc = wmi_start_search(wil);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	if (rc) {
		wil_err(wil, "wmi_start_search failed\n");
		goto out_stop;
	}

	p2p->discovery_started = 1;
	INIT_WORK(&p2p->discovery_expired_work, wil_p2p_search_expired);
	mod_timer(&p2p->discovery_timer,
		  jiffies + msecs_to_jiffies(P2P_SEARCH_DURATION_MS));

out_stop:
	if (rc)
<<<<<<< HEAD
		wmi_stop_discovery(vif);
=======
		wmi_stop_discovery(wil);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

out:
	return rc;
}

int wil_p2p_listen(struct wil6210_priv *wil, struct wireless_dev *wdev,
		   unsigned int duration, struct ieee80211_channel *chan,
		   u64 *cookie)
{
<<<<<<< HEAD
	struct wil6210_vif *vif = wdev_to_vif(wil, wdev);
	struct wil_p2p_info *p2p = &vif->p2p;
=======
	struct wil_p2p_info *p2p = &wil->p2p;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	int rc;

	if (!chan)
		return -EINVAL;

	wil_dbg_misc(wil, "p2p_listen: duration %d\n", duration);

	mutex_lock(&wil->mutex);

	if (p2p->discovery_started) {
		wil_err(wil, "discovery already ongoing\n");
		rc = -EBUSY;
		goto out;
	}

	memcpy(&p2p->listen_chan, chan, sizeof(*chan));
	*cookie = ++p2p->cookie;
	p2p->listen_duration = duration;

<<<<<<< HEAD
	mutex_lock(&wil->vif_mutex);
	if (vif->scan_request) {
=======
	mutex_lock(&wil->p2p_wdev_mutex);
	if (wil->scan_request) {
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		wil_dbg_misc(wil, "Delaying p2p listen until scan done\n");
		p2p->pending_listen_wdev = wdev;
		p2p->discovery_started = 1;
		rc = 0;
<<<<<<< HEAD
		mutex_unlock(&wil->vif_mutex);
		goto out;
	}
	mutex_unlock(&wil->vif_mutex);

	rc = wil_p2p_start_listen(vif);
=======
		mutex_unlock(&wil->p2p_wdev_mutex);
		goto out;
	}
	mutex_unlock(&wil->p2p_wdev_mutex);

	rc = wil_p2p_start_listen(wil);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	if (rc)
		goto out;

	p2p->discovery_started = 1;
<<<<<<< HEAD
	if (vif->mid == 0)
		wil->radio_wdev = wdev;
=======
	wil->radio_wdev = wdev;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	cfg80211_ready_on_channel(wdev, *cookie, chan, duration,
				  GFP_KERNEL);

out:
	mutex_unlock(&wil->mutex);
	return rc;
}

<<<<<<< HEAD
u8 wil_p2p_stop_discovery(struct wil6210_vif *vif)
{
	struct wil_p2p_info *p2p = &vif->p2p;
=======
u8 wil_p2p_stop_discovery(struct wil6210_priv *wil)
{
	struct wil_p2p_info *p2p = &wil->p2p;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	u8 started = p2p->discovery_started;

	if (p2p->discovery_started) {
		if (p2p->pending_listen_wdev) {
			/* discovery not really started, only pending */
			p2p->pending_listen_wdev = NULL;
		} else {
			del_timer_sync(&p2p->discovery_timer);
<<<<<<< HEAD
			wmi_stop_discovery(vif);
=======
			wmi_stop_discovery(wil);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		}
		p2p->discovery_started = 0;
	}

	return started;
}

<<<<<<< HEAD
int wil_p2p_cancel_listen(struct wil6210_vif *vif, u64 cookie)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	struct wil_p2p_info *p2p = &vif->p2p;
=======
int wil_p2p_cancel_listen(struct wil6210_priv *wil, u64 cookie)
{
	struct wil_p2p_info *p2p = &wil->p2p;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	u8 started;

	mutex_lock(&wil->mutex);

	if (cookie != p2p->cookie) {
		wil_info(wil, "Cookie mismatch: 0x%016llx vs. 0x%016llx\n",
			 p2p->cookie, cookie);
		mutex_unlock(&wil->mutex);
		return -ENOENT;
	}

<<<<<<< HEAD
	started = wil_p2p_stop_discovery(vif);
=======
	started = wil_p2p_stop_discovery(wil);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	mutex_unlock(&wil->mutex);

	if (!started) {
		wil_err(wil, "listen not started\n");
		return -ENOENT;
	}

<<<<<<< HEAD
	mutex_lock(&wil->vif_mutex);
	cfg80211_remain_on_channel_expired(vif_to_radio_wdev(wil, vif),
					   p2p->cookie,
					   &p2p->listen_chan,
					   GFP_KERNEL);
	if (vif->mid == 0)
		wil->radio_wdev = wil->main_ndev->ieee80211_ptr;
	mutex_unlock(&wil->vif_mutex);
=======
	mutex_lock(&wil->p2p_wdev_mutex);
	cfg80211_remain_on_channel_expired(wil->radio_wdev,
					   p2p->cookie,
					   &p2p->listen_chan,
					   GFP_KERNEL);
	wil->radio_wdev = wil->wdev;
	mutex_unlock(&wil->p2p_wdev_mutex);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	return 0;
}

void wil_p2p_listen_expired(struct work_struct *work)
{
	struct wil_p2p_info *p2p = container_of(work,
			struct wil_p2p_info, discovery_expired_work);
<<<<<<< HEAD
	struct wil6210_vif *vif = container_of(p2p,
			struct wil6210_vif, p2p);
	struct wil6210_priv *wil = vif_to_wil(vif);
=======
	struct wil6210_priv *wil = container_of(p2p,
			struct wil6210_priv, p2p);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	u8 started;

	wil_dbg_misc(wil, "p2p_listen_expired\n");

	mutex_lock(&wil->mutex);
<<<<<<< HEAD
	started = wil_p2p_stop_discovery(vif);
	mutex_unlock(&wil->mutex);

	if (!started)
		return;

	mutex_lock(&wil->vif_mutex);
	cfg80211_remain_on_channel_expired(vif_to_radio_wdev(wil, vif),
					   p2p->cookie,
					   &p2p->listen_chan,
					   GFP_KERNEL);
	if (vif->mid == 0)
		wil->radio_wdev = wil->main_ndev->ieee80211_ptr;
	mutex_unlock(&wil->vif_mutex);
=======
	started = wil_p2p_stop_discovery(wil);
	mutex_unlock(&wil->mutex);

	if (started) {
		mutex_lock(&wil->p2p_wdev_mutex);
		cfg80211_remain_on_channel_expired(wil->radio_wdev,
						   p2p->cookie,
						   &p2p->listen_chan,
						   GFP_KERNEL);
		wil->radio_wdev = wil->wdev;
		mutex_unlock(&wil->p2p_wdev_mutex);
	}

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

void wil_p2p_search_expired(struct work_struct *work)
{
	struct wil_p2p_info *p2p = container_of(work,
			struct wil_p2p_info, discovery_expired_work);
<<<<<<< HEAD
	struct wil6210_vif *vif = container_of(p2p,
			struct wil6210_vif, p2p);
	struct wil6210_priv *wil = vif_to_wil(vif);
=======
	struct wil6210_priv *wil = container_of(p2p,
			struct wil6210_priv, p2p);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	u8 started;

	wil_dbg_misc(wil, "p2p_search_expired\n");

	mutex_lock(&wil->mutex);
<<<<<<< HEAD
	started = wil_p2p_stop_discovery(vif);
=======
	started = wil_p2p_stop_discovery(wil);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	mutex_unlock(&wil->mutex);

	if (started) {
		struct cfg80211_scan_info info = {
			.aborted = false,
		};

<<<<<<< HEAD
		mutex_lock(&wil->vif_mutex);
		if (vif->scan_request) {
			cfg80211_scan_done(vif->scan_request, &info);
			vif->scan_request = NULL;
			if (vif->mid == 0)
				wil->radio_wdev =
					wil->main_ndev->ieee80211_ptr;
		}
		mutex_unlock(&wil->vif_mutex);
=======
		mutex_lock(&wil->p2p_wdev_mutex);
		if (wil->scan_request) {
			cfg80211_scan_done(wil->scan_request, &info);
			wil->scan_request = NULL;
			wil->radio_wdev = wil->wdev;
		}
		mutex_unlock(&wil->p2p_wdev_mutex);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	}
}

void wil_p2p_delayed_listen_work(struct work_struct *work)
{
	struct wil_p2p_info *p2p = container_of(work,
			struct wil_p2p_info, delayed_listen_work);
<<<<<<< HEAD
	struct wil6210_vif *vif = container_of(p2p,
			struct wil6210_vif, p2p);
	struct wil6210_priv *wil = vif_to_wil(vif);
=======
	struct wil6210_priv *wil = container_of(p2p,
			struct wil6210_priv, p2p);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	int rc;

	mutex_lock(&wil->mutex);

	wil_dbg_misc(wil, "Checking delayed p2p listen\n");
	if (!p2p->discovery_started || !p2p->pending_listen_wdev)
		goto out;

<<<<<<< HEAD
	mutex_lock(&wil->vif_mutex);
	if (vif->scan_request) {
		/* another scan started, wait again... */
		mutex_unlock(&wil->vif_mutex);
		goto out;
	}
	mutex_unlock(&wil->vif_mutex);

	rc = wil_p2p_start_listen(vif);

	mutex_lock(&wil->vif_mutex);
=======
	mutex_lock(&wil->p2p_wdev_mutex);
	if (wil->scan_request) {
		/* another scan started, wait again... */
		mutex_unlock(&wil->p2p_wdev_mutex);
		goto out;
	}
	mutex_unlock(&wil->p2p_wdev_mutex);

	rc = wil_p2p_start_listen(wil);

	mutex_lock(&wil->p2p_wdev_mutex);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	if (rc) {
		cfg80211_remain_on_channel_expired(p2p->pending_listen_wdev,
						   p2p->cookie,
						   &p2p->listen_chan,
						   GFP_KERNEL);
<<<<<<< HEAD
		if (vif->mid == 0)
			wil->radio_wdev = wil->main_ndev->ieee80211_ptr;
=======
		wil->radio_wdev = wil->wdev;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	} else {
		cfg80211_ready_on_channel(p2p->pending_listen_wdev, p2p->cookie,
					  &p2p->listen_chan,
					  p2p->listen_duration, GFP_KERNEL);
<<<<<<< HEAD
		if (vif->mid == 0)
			wil->radio_wdev = p2p->pending_listen_wdev;
	}
	p2p->pending_listen_wdev = NULL;
	mutex_unlock(&wil->vif_mutex);
=======
		wil->radio_wdev = p2p->pending_listen_wdev;
	}
	p2p->pending_listen_wdev = NULL;
	mutex_unlock(&wil->p2p_wdev_mutex);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

out:
	mutex_unlock(&wil->mutex);
}

void wil_p2p_stop_radio_operations(struct wil6210_priv *wil)
{
<<<<<<< HEAD
	struct wil6210_vif *vif = ndev_to_vif(wil->main_ndev);
	struct wil_p2p_info *p2p = &vif->p2p;
=======
	struct wil_p2p_info *p2p = &wil->p2p;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	struct cfg80211_scan_info info = {
		.aborted = true,
	};

	lockdep_assert_held(&wil->mutex);
<<<<<<< HEAD
	lockdep_assert_held(&wil->vif_mutex);
=======
	lockdep_assert_held(&wil->p2p_wdev_mutex);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	if (wil->radio_wdev != wil->p2p_wdev)
		goto out;

	if (!p2p->discovery_started) {
		/* Regular scan on the p2p device */
<<<<<<< HEAD
		if (vif->scan_request &&
		    vif->scan_request->wdev == wil->p2p_wdev)
			wil_abort_scan(vif, true);
=======
		if (wil->scan_request &&
		    wil->scan_request->wdev == wil->p2p_wdev)
			wil_abort_scan(wil, true);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		goto out;
	}

	/* Search or listen on p2p device */
<<<<<<< HEAD
	mutex_unlock(&wil->vif_mutex);
	wil_p2p_stop_discovery(vif);
	mutex_lock(&wil->vif_mutex);

	if (vif->scan_request) {
		/* search */
		cfg80211_scan_done(vif->scan_request, &info);
		vif->scan_request = NULL;
=======
	mutex_unlock(&wil->p2p_wdev_mutex);
	wil_p2p_stop_discovery(wil);
	mutex_lock(&wil->p2p_wdev_mutex);

	if (wil->scan_request) {
		/* search */
		cfg80211_scan_done(wil->scan_request, &info);
		wil->scan_request = NULL;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	} else {
		/* listen */
		cfg80211_remain_on_channel_expired(wil->radio_wdev,
						   p2p->cookie,
						   &p2p->listen_chan,
						   GFP_KERNEL);
	}

out:
<<<<<<< HEAD
	wil->radio_wdev = wil->main_ndev->ieee80211_ptr;
=======
	wil->radio_wdev = wil->wdev;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}
