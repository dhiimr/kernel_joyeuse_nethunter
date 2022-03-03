#ifndef _LINUX_RPMSG_QCOM_GLINK_H
#define _LINUX_RPMSG_QCOM_GLINK_H

#include <linux/device.h>

struct qcom_glink;
<<<<<<< HEAD
struct glink_spi;
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

#if IS_ENABLED(CONFIG_RPMSG_QCOM_GLINK_SMEM)

struct qcom_glink *qcom_glink_smem_register(struct device *parent,
					    struct device_node *node);
void qcom_glink_smem_unregister(struct qcom_glink *glink);

#else

static inline struct qcom_glink *
qcom_glink_smem_register(struct device *parent,
			 struct device_node *node)
{
	return NULL;
}

static inline void qcom_glink_smem_unregister(struct qcom_glink *glink) {}

#endif

<<<<<<< HEAD

#if IS_ENABLED(CONFIG_RPMSG_QCOM_GLINK_SPSS)

struct qcom_glink *qcom_glink_spss_register(struct device *parent,
					    struct device_node *node);
void qcom_glink_spss_unregister(struct qcom_glink *glink);

#else

static inline struct qcom_glink *
qcom_glink_spss_register(struct device *parent,
			 struct device_node *node)
{
	return NULL;
}

static inline void qcom_glink_spss_unregister(struct qcom_glink *glink) {}

#endif


#if IS_ENABLED(CONFIG_RPMSG_QCOM_GLINK_SPI)

struct glink_spi *qcom_glink_spi_register(struct device *parent,
					       struct device_node *node);
void qcom_glink_spi_unregister(struct glink_spi *glink);

#else

static inline struct glink_spi *
qcom_glink_spi_register(struct device *parent, struct device_node *node)
{
	return NULL;
}

static inline void qcom_glink_spi_unregister(struct glink_spi *glink) {}

#endif


=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
#endif
